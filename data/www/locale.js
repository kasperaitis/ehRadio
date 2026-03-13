// i18n loader for ehRadio
// Loads locale.json if it exists, provides translation functions
var i18n = {};

// Always try to load locale.json - if it doesn't exist or is English, server won't have it
fetch('locale.json?' + (typeof radioVersion !== 'undefined' ? radioVersion : ''))
    .then(function(r){ return r.ok ? r.json() : Promise.reject('not-ok'); })
    .then(function(data){ 
        i18n = data;
        applyI18n(); // Only apply translations when successfully loaded
    })
    .catch(function(){
        console.warn('locale.json not found or failed to load, using hardcoded HTML text');
        // Don't run applyI18n() - let HTML fallbacks handle it
    });

function t(key) {
  var args = Array.prototype.slice.call(arguments, 1);
  var s = (i18n && i18n[key]) ? i18n[key] : key;
  args.forEach(function(a, i){ s = s.replace('{' + i + '}', a); });
  return s;
}

function applyI18n(root) {
  (root || document).querySelectorAll('[data-i18n]').forEach(function(el) {
    var key = el.dataset.i18n;
    var val = i18n[key];
    if (!val) return;
    if (el.tagName === 'INPUT' && (el.type === 'button' || el.type === 'submit')) {
      el.value = val;
    } else if (el.tagName === 'INPUT' && el.placeholder !== undefined) {
      el.placeholder = val;
    } else {
      el.textContent = val;
    }
  });
  
  // Update knob on/off labels via CSS variables (must be quoted for content property)
  document.documentElement.style.setProperty('--knob-off', '"' + t('lbl_off', 'Off') + '"');
  document.documentElement.style.setProperty('--knob-on', '"' + t('lbl_on', 'On') + '"');
}
