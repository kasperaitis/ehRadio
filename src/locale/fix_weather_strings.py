#!/usr/bin/env python3
"""Remove weather API strings and add translatable weather labels to all displayL10n files"""
import re
from pathlib import Path

# Find all displayL10n_*.h files
locale_files = list(Path('.').glob('displayL10n_*.h'))

# Weather label translations for each language
weather_labels = {
    'en_US': ('feels like:', 'pressure:', 'humidity:', 'wind:'),
    'ru_RU': ('ощущается:', 'давление:', 'влажность:', 'ветер:'),
    'de_DE': ('gefühlt:', 'Druck:', 'Luftfeuchtigkeit:', 'Wind:'),
    'fr_FR': ('ressenti:', 'pression:', 'humidité:', 'vent:'),
    'es_ES': ('sensación:', 'presión:', 'humedad:', 'viento:'),
    'it_IT': ('percepita:', 'pressione:', 'umidità:', 'vento:'),
    'pt_PT': ('sensação:', 'pressão:', 'humidade:', 'vento:'),
    'pl_PL': ('odczuwalna:', 'ciśnienie:', 'wilgotność:', 'wiatr:'),
    'nl_NL': ('gevoelstemperatuur:', 'druk:', 'vochtigheid:', 'wind:'),
    'cs_CZ': ('pocit:', 'tlak:', 'vlhkost:', 'vítr:'),
    'sk_SK': ('pocit:', 'tlak:', 'vlhkosť:', 'vietor:'),
    'da_DK': ('føles som:', 'tryk:', 'fugtighed:', 'vind:'),
    'no_NO': ('føles som:', 'trykk:', 'fuktighet:', 'vind:'),
    'sv_SE': ('känns som:', 'tryck:', 'fuktighet:', 'vind:'),
    'fi_FI': ('tuntuu kuin:', 'paine:', 'kosteus:', 'tuuli:'),
    'hu_HU': ('hőérzet:', 'légnyomás:', 'páratartalom:', 'szél:'),
    'ro_RO': ('resimțit:', 'presiune:', 'umiditate:', 'vânt:'),
    'bg_BG': ('усеща се:', 'налягане:', 'влажност:', 'вятър:'),
    'hr_HR': ('osjeća se:', 'tlak:', 'vlažnost:', 'vjetar:'),
    'sr_RS': ('осећај:', 'притисак:', 'влажност:', 'ветар:'),
    'sl_SI': ('občutek:', 'pritisk:', 'vlažnost:', 'veter:'),
    'bs_BA': ('osjeća se:', 'pritisak:', 'vlažnost:', 'vjetar:'),
    'mk_MK': ('чувствува:', 'притисок:', 'влажност:', 'ветер:'),
    'el_GR': ('αίσθηση:', 'πίεση:', 'υγρασία:', 'άνεμος:'),
    'uk_UA': ('відчувається:', 'тиск:', 'вологість:', 'вітер:'),
    'be_BY': ('адчуваецца:', 'ціск:', 'вільготнасць:', 'вецер:'),
    'tr_TR': ('hissedilen:', 'basınç:', 'nem:', 'rüzgar:'),
    'et_EE': ('tundub:', 'rõhk:', 'niiskus:', 'tuul:'),
    'lv_LV': ('sajūta:', 'spiediens:', 'mitrums:', 'vējš:'),
    'lt_LT': ('jaučiasi:', 'slėgis:', 'drėgmė:', 'vėjas:'),
    'is_IS': ('finnst:', 'þrýstingur:', 'raki:', 'vindur:'),
    'kk_KZ': ('сезіледі:', 'қысым:', 'ылғал:', 'жел:'),
    'ky_KG': ('сезилет:', 'басым:', 'нымдуулук:', 'шамал:'),
    'tg_TJ': ('ҳис:', 'фишор:', 'намӣ:', 'бод:'),
    'uz_UZ': ('his qilish:', 'bosim:', 'namlik:', 'shamol:'),
    'mn_MN': ('мэдрэх:', 'даралт:', 'чийгшил:', 'салхи:'),
    'me_ME': ('осећај:', 'притисак:', 'влажност:', 'ветар:'),
}

print('Updating displayL10n files to remove weather API strings and add translatable labels...\n')

for filepath in locale_files:
    locale_code = filepath.stem.replace('displayL10n_', '')
    
    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # Remove const_getWeather line
    content = re.sub(r'const char const_getWeather\[\].*PROGMEM = .*;\n', '', content)
    
    # Remove weatherUnits and weatherLang lines  
    content = re.sub(r'const char\s+weatherUnits\[\].*PROGMEM = .*;\s*/\*.*\*/\n', '', content)
    content = re.sub(r'const char\s+weatherLang\[\].*PROGMEM = .*;\s*/\*.*\*/\n', '', content)
    
    # Get weather labels for this language (default to English if not found)
    labels = weather_labels.get(locale_code, weather_labels['en_US'])
    
    # Add new weather label strings before the weatherFmt definition
    weather_string_block = f'''const char weather_feelslike[]  PROGMEM = "{labels[0]}";
const char weather_pressure[]   PROGMEM = "{labels[1]}";
const char weather_humidity[]   PROGMEM = "{labels[2]}";
const char weather_wind[]       PROGMEM = "{labels[3]}";

'''
    
    # Insert before #if EXT_WEATHER or #ifdef UPDATEURL section (whichever comes first)
    # Find the weatherFmt line
    match = re.search(r'(#if EXT_WEATHER\nconst char\s+weatherFmt)', content)
    if match:
        content = content[:match.start()] + weather_string_block + content[match.start():]
    
    with open(filepath, 'w', encoding='utf-8') as f:
        f.write(content)
    
    print(f'✓ {filepath.name} - Updated')

print(f'\n{"="*60}')
print(f'Updated {len(locale_files)} displayL10n files')
print('Removed: const_getWeather, weatherUnits, weatherLang')
print('Added: weather_feelslike, weather_pressure, weather_humidity, weather_wind')
