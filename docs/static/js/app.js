let currentLang = 'french';
let currentType = 'items';
let currentGame = 'bg2ee';
let currentMod = 'all';
let currentData = '';
let filteredData = [];
let filterItemType = "";
let filterItemEnchant = "";
let filterSpellLevel = "";
let filterSpellSchool = "";
let data = [];
let showDiffs = false;

const gameIcons = document.getElementById('game-icons');
const searchInput = document.getElementById('search');
const modInput = document.getElementById('mod');
const descriptions = document.getElementById('descriptions');
const toggleDiffsButton = document.getElementById('toggle-diffs');
const filterSetup = {
    language: value => {
        currentLang = value;
        showLoading(true);
        setTimeout(() => loadData(), 0);
    },
    'filter-item-type': value => {
        filterItemType = value;
        render();
    },
    'filter-item-enchant': value => {
        filterItemEnchant = value;
        render();
    },
    'filter-spell-level': value => {
        filterSpellLevel = value;
        render();
    },
    'filter-spell-school': value => {
        filterSpellSchool = value;
        render();
    },
    type: value => {
        currentType = value;
        ['filter-item-type', 'filter-item-enchant', 'filter-spell-school', 'filter-spell-level'].forEach(resetCustomSelect);
        filterItemType = filterItemEnchant = filterSpellLevel = filterSpellSchool = "";
        document.getElementById('object-filters').classList.toggle('hidden', currentType !== 'items');
        document.getElementById('spell-filters').classList.toggle('hidden', currentType !== 'spells');
        loadData();
    }
};

function processVisibleEntries() {
    const query = searchInput.value.toLowerCase();
    const viewportHeight = window.innerHeight;

    document.querySelectorAll('.entry').forEach(entryEl => {
        const rect = entryEl.getBoundingClientRect();
        if (rect.bottom < 0 || rect.top > viewportHeight) return;

        const id = entryEl.dataset.id;
        const entry = filteredData.find(e => e.id === id);

        if (!entry) return;

        const originalEl = entryEl.querySelector('.original pre');
        const moddedEl = entryEl.querySelector('.modded pre');

        entryEl.querySelector('h2').innerHTML = `${highlightQuery(entry.name, query)}<span>${entry.id}</span>`;

        if (entryEl.dataset.diffed === "true") {
            if (entryEl.dataset.highlighted !== query) {
                originalEl.innerHTML = highlightQuery(entry.original, query);
                moddedEl.innerHTML = highlightQuery(entry.modded, query);
                entryEl.dataset.highlighted = query;
            }
            return;
        }

        if (!showDiffs) {
            originalEl.innerHTML = highlightQuery(entry.original, query);
            moddedEl.innerHTML = highlightQuery(entry.modded, query);
            entryEl.dataset.highlighted = query;
            return;
        }

        const [originalHTML, moddedHTML] = diffWords(entry.original, entry.modded);
        originalEl.innerHTML = highlightQuery(originalHTML, query);
        moddedEl.innerHTML = highlightQuery(moddedHTML, query);
        entryEl.dataset.diffed = "true";
        entryEl.dataset.highlighted = query;
    });
}

function setupCustomSelect(containerId, callback) {
    const container = document.getElementById(containerId);

    if (!container) return;

    const toggle = container.querySelector('.selected');
    const menu = container.querySelector('.options');
    const options = menu.querySelectorAll('[data-value]');

    let isOpen = false;

    function closeMenu() {
        isOpen = false;
        menu.classList.remove('open');
    }

    function openMenu() {
        isOpen = true;
        menu.classList.add('open');
    }

    toggle.addEventListener('click', () => {
        if (toggle.getAttribute('aria-disabled') === 'true') return;
        isOpen ? closeMenu() : openMenu();
    });

    document.addEventListener('click', (e) => {
        if (!container.contains(e.target)) closeMenu();
    });

    options.forEach(option => {
        option.addEventListener('click', () => {
            const selectedValue = option.dataset.value;
            options.forEach(o => o.classList.remove('active'));
            option.classList.add('active');
            toggle.innerHTML = option.innerHTML;
            closeMenu();
            if (typeof callback === 'function') callback(selectedValue);
        });
    });
}

function resetCustomSelect(containerId) {
    const container = document.getElementById(containerId);
    if (!container) return;

    const toggle = container.querySelector('.selected');
    const firstOption = container.querySelector('.options [data-value]');
    const options = container.querySelectorAll('.options [data-value]');

    if (firstOption) {
        options.forEach(o => o.classList.remove('active'));
        firstOption.classList.add('active');
        toggle.innerHTML = firstOption.innerHTML;
        const callback = container.dataset.callback;
        if (callback && typeof window[callback] === 'function') {
            window[callback](firstOption.dataset.value);
        }
    }
}

function setFiltersEnabled(enabled) {
    [searchInput, toggleDiffsButton].forEach(input => input.disabled = !enabled);
    document.querySelectorAll('#filter-item-type, #filter-item-enchant, #filter-spell-school, #filter-spell-level')
        .forEach(cs => {
            cs.classList.toggle('disabled', !enabled);
            cs.querySelector('.selected').toggleAttribute('aria-disabled', !enabled);
        });
}

function loadData() {
    if (!currentGame) {
        descriptions.innerHTML = '<p style="padding:1em;">Veuillez choisir un jeu pour afficher les données.</p>';
        return setFiltersEnabled(false);
    }

    const key = `${currentLang}-${currentGame}-${currentMod}-${currentType}`;
    const scriptPath = `data/${key}.js`;

    if (currentData == key) {
        setFiltersEnabled(true);
        return;
    }
    showLoading(true);
    data = [];

    if (!window.loadedData || !window.loadedData[key]) {
        const script = document.createElement('script');
        script.src = scriptPath;
        script.onload = () => {
            data = window.loadedData[key] || [];
            setFiltersEnabled(true);
            render();
            showLoading(false);
        };
        script.onerror = () => {
            descriptions.innerHTML = `<p style="padding:1em; color: red;">Fichier non trouvé : ${scriptPath}</p>`;
            setFiltersEnabled(false);
            showLoading(false);
        };
        document.head.appendChild(script);
    } else {
        data = window.loadedData[key];
        setFiltersEnabled(true);
        render();
        showLoading(false);
    }
    currentData = key;
}

function showLoading(show) {
    const loading = document.getElementById('loading');

    if (loading) loading.classList.toggle('hidden', !show);
}

function diffWords(oldStr, newStr) {
    const dmp = new diff_match_patch();
    const diffs = dmp.diff_main(oldStr, newStr);
    dmp.diff_cleanupSemantic(diffs);
    return diffs.reduce(([oldDiff, newDiff], [operation, data]) => {
        if (operation === 0) return [oldDiff + data, newDiff + data];
        if (operation === -1) return [oldDiff + `<span class="diff removed">${data}</span>`, newDiff];
        return [oldDiff, newDiff + `<span class="diff added">${data}</span>`];
    }, ['', '']);
}

function highlightQuery(text, query) {
    if (!query) return text;
    const safeQuery = query.replace(/[.*+?^${}()|[\]\\]/g, '\\$&');
    const regex = new RegExp(`(${safeQuery})`, 'gi');
    return text.replace(regex, '<mark>$1</mark>');
}

function render(resetScroll = true) {
    const query = searchInput.value.toLowerCase();
    if (resetScroll) {
        descriptions.innerHTML = '';
        requestAnimationFrame(() => window.scrollTo({top: 0}));
    }

    filteredData = data.filter(entry => {
        if (query &&
            !entry.name.toLowerCase().includes(query) &&
            !entry.original.toLowerCase().includes(query) &&
            !entry.modded.toLowerCase().includes(query)
        ) return false;

        if (currentType === 'items') {
            if (filterItemType && String(entry.type) !== filterItemType) return false;
            if (filterItemEnchant && String(entry.level) !== filterItemEnchant) return false;
        } else if (currentType === 'spells') {
            if (filterSpellSchool && String(entry.type) !== filterSpellSchool) return false;
            if (filterSpellLevel && String(entry.level) !== filterSpellLevel) return false;
        }

        return true;
    });

    // Mise à jour DOM sans tout régénérer
    const existingEntries = new Set();
    filteredData.forEach(entry => {
        let entryEl = document.querySelector(`.entry[data-id="${entry.id}"]`);
        if (!entryEl) {
            entryEl = document.createElement('div');
            entryEl.className = 'entry';
            entryEl.dataset.id = entry.id;
            entryEl.dataset.type = entry.type || '';
            entryEl.dataset.level = entry.level || '';
            entryEl.innerHTML = `
                <h2>${entry.name}<span>${entry.id}</span></h2>
                <div class="comparison">
                    <div class="original"><pre>${entry.original}</pre></div>
                    <div class="modded"><pre>${entry.modded}</pre></div>
                </div>
            `;
            descriptions.appendChild(entryEl);
        }
        entryEl.style.display = '';
        existingEntries.add(entry.id);
    });

    document.querySelectorAll('.entry:not([style*="display: none"])').forEach(entryEl => {
        if (!existingEntries.has(entryEl.dataset.id)) {
            entryEl.style.display = 'none';
        }
    });

    updateEntryCount();

    if (!showDiffs) {
        document.querySelectorAll('.entry[data-diffed]').forEach(entryEl => {
            const entry = filteredData.find(e => e.id === entryEl.dataset.id);
            if (!entry) return;

            entryEl.querySelector('.original pre').textContent = entry.original;
            entryEl.querySelector('.modded pre').textContent = entry.modded;
            delete entryEl.dataset.diffed;
            delete entryEl.dataset.highlighted;
        });
    }

    if (searchInput.value || showDiffs) processVisibleEntries();
}

function updateEntryCount() {
    const el = document.getElementById('entry-count');
    if (el) {
        el.innerHTML = `<span>${filteredData.length}</span> ${filteredData.length === 1 ? 'élément' : 'éléments'}`;
    }
}

function debounce(fn, delay = 200) {
    let timeout;
    return function (...args) {
        clearTimeout(timeout);
        timeout = setTimeout(() => fn.apply(this, args), delay);
    };
}

window.addEventListener('scroll', () => {
    if (searchInput.value || showDiffs) processVisibleEntries();
});

Object.entries(filterSetup).forEach(([id, callback]) => setupCustomSelect(id, callback));

toggleDiffsButton.addEventListener('click', () => {
    showDiffs = !showDiffs;
    toggleDiffsButton.classList.toggle('active', showDiffs);
    render(false);
});

searchInput.addEventListener('input', debounce(render, 200));

document.addEventListener('DOMContentLoaded', () => {
    const modScript = document.createElement('script');
    modScript.src = 'data/mods.js';
    modScript.onload = () => {
        const optionsContainer = modInput.querySelector('.options');
        const selected = modInput.querySelector('.selected');

        optionsContainer.innerHTML = '';
        window.loadedMods.forEach(mod => {
            const div = document.createElement('div');
            div.className = 'option';
            div.dataset.value = mod;
            div.textContent = mod;
            optionsContainer.appendChild(div);
        });

        selected.textContent = window.loadedMods[0] || 'all';
        selected.removeAttribute('aria-disabled');
        modInput.dataset.value = window.loadedMods[0] || '';
        setupCustomSelect('mod', value => {
            currentMod = value;
            loadData();
        });
        loadData();
    };
    document.head.appendChild(modScript);

    gameIcons.addEventListener('click', e => {
        const button = e.target.closest('button[data-key]');
        if (button) {
            currentGame = button.dataset.key;
            gameIcons.querySelectorAll('button').forEach(btn =>
                btn.classList.toggle('active', btn.dataset.key === currentGame)
            );
            setFiltersEnabled(false);
            loadData();
        }
    });
    loadData();
});
