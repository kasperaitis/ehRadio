let dragged, id, index, indexDrop, list;
let scrollInterval = null;
let lastX = 0, lastY = 0;
let touchTimeout = null;
let startX = 0, startY = 0;
const LONG_PRESS_DELAY = 1000;

function getLi(el) {
	while (el && el !== document.body && el !== null) {
		if (el.classList && el.classList.contains('pleitem')) return el;
		el = el.parentNode;
	}
	return null;
}

function clearIndicators() {
	const items = document.querySelectorAll('.pleitem');
	items.forEach(item => {
		item.classList.remove('drag-over-above', 'drag-over-below');
	});
}

function stopAutoScroll() {
	if (scrollInterval) {
		clearInterval(scrollInterval);
		scrollInterval = null;
	}
}

function handleAutoScroll(x, y) {
	if (!dragged) return;
	const container = document.getElementById('pleditorcontent');
	if (!container) return;
	const rect = container.getBoundingClientRect();
	const threshold = 50;
	let direction = 0;

	if (y < rect.top + threshold) direction = -1;
	else if (y > rect.bottom - threshold) direction = 1;

	lastX = x;
	lastY = y;

	if (direction !== 0) {
		if (!scrollInterval) {
			scrollInterval = setInterval(() => {
				container.scrollTop += direction * 8;
				const target = document.elementFromPoint(lastX, lastY);
				const targetLi = getLi(target);
				setIndicator({ clientX: lastX, clientY: lastY }, targetLi);
			}, 25);
		}
	} else {
		stopAutoScroll();
	}
}

function updateIndices() {
	let items = document.getElementById('pleditorcontent').getElementsByTagName('li');
	for (let i = 0; i < items.length; i++) {
		items[i].getElementsByTagName('span')[0].innerText = ("00" + (i + 1)).slice(-3);
	}
}

function startDrag(target) {
	const li = getLi(target);
	if (li) {
		dragged = li;
		id = li.id;
		list = li.parentNode.children;
		for (let i = 0; i < list.length; i += 1) {
			if (list[i] === dragged) {
				index = i;
				break;
			}
		}
		dragged.classList.add('dragging');
	}
}

function setIndicator(e, targetLi) {
	if (!dragged || !targetLi || targetLi === dragged) {
		clearIndicators();
		return;
	}
	const rect = targetLi.getBoundingClientRect();
	const mouseY = (e.touches && e.touches.length > 0) ? e.touches[0].clientY : (e.clientY || e.pageY || 0);
	const threshold = rect.top + rect.height / 2;
	
	clearIndicators();
	if (mouseY < threshold) {
		targetLi.classList.add('drag-over-above');
	} else {
		targetLi.classList.add('drag-over-below');
	}
}

function doDrop(target) {
	stopAutoScroll();
	const targetLi = getLi(target);
	if (dragged && targetLi && targetLi !== dragged) {
		const isAbove = targetLi.classList.contains('drag-over-above');
		dragged.remove();
		for (let i = 0; i < list.length; i += 1) {
			if (list[i] === targetLi) {
				indexDrop = i;
				break;
			}
		}
		if (isAbove) {
			targetLi.before(dragged);
		} else {
			targetLi.after(dragged);
		}
		updateIndices();
	}
	if (dragged) dragged.classList.remove('dragging');
	clearIndicators();
	dragged = null;
}

document.addEventListener("dragstart", (e) => {
	if (e.target.classList.contains('grabbable')) {
		startDrag(e.target);
	}
});

document.addEventListener("dragover", (e) => {
	e.preventDefault();
	handleAutoScroll(e.clientX, e.clientY);
	const targetLi = getLi(e.target);
	setIndicator(e, targetLi);
});

document.addEventListener("drop", (e) => {
	doDrop(e.target);
});

document.addEventListener("dragend", (e) => {
	stopAutoScroll();
	if (dragged) dragged.classList.remove('dragging');
	clearIndicators();
	dragged = null;
});

// Mobile/Touch Support
document.addEventListener("touchstart", (e) => {
	if (e.target.classList.contains('grabbable')) {
		const touch = e.touches[0];
		startX = touch.clientX;
		startY = touch.clientY;
		const target = e.target;
		touchTimeout = setTimeout(() => {
			startDrag(target);
			if (navigator.vibrate) navigator.vibrate(50); // Haptic feedback when grab starts
		}, LONG_PRESS_DELAY);
	}
}, { passive: false });

document.addEventListener("touchmove", (e) => {
	const touch = e.touches[0];
	if (touchTimeout && !dragged) {
		const moveX = Math.abs(touch.clientX - startX);
		const moveY = Math.abs(touch.clientY - startY);
		if (moveX > 10 || moveY > 10) {
			clearTimeout(touchTimeout);
			touchTimeout = null;
		}
	}
	if (dragged) {
		e.preventDefault(); // Prevent scrolling
		handleAutoScroll(touch.clientX, touch.clientY);
		const target = document.elementFromPoint(touch.clientX, touch.clientY);
		const targetLi = getLi(target);
		setIndicator(e, targetLi);
	}
}, { passive: false });

document.addEventListener("touchend", (e) => {
	if (touchTimeout) {
		clearTimeout(touchTimeout);
		touchTimeout = null;
	}
	if (dragged) {
		stopAutoScroll();
		const touch = e.changedTouches[0];
		const target = document.elementFromPoint(touch.clientX, touch.clientY);
		doDrop(target);
	}
});
