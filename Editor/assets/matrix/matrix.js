function LedMatrix(rootId, width, height) {
  const root = document.getElementById(rootId);
  const rows = [];

  function iterateAll(rowCallback, indexCallback) {
    for (let row = 0; row < height; row++) {
      rowCallback && rowCallback(row);
      for (let index = 0; index < width; index++) {
        indexCallback && indexCallback(row, index);
      }
    }
  }

  function updateBit(row, index) {
    const bit = rows[row][index];
    if (bit.value) {
      bit.element.classList.add('active');
    } else {
      bit.element.classList.remove('active');
    }
  }

  function update() {
    iterateAll(null, updateBit);
  }

  function setBit(row, index, value) {
    rows[row][index].value = value;
  }

  function toggleBit(row, index) {
    setBit(row, index, !rows[row][index].value);
  }

  function clear() {
    iterateAll(null, (row, index) => {
      setBit(row, index, false);
      updateBit(row, index);
    });
  }

  function createBit(row, index) {
    const button = document.createElement('button');
    button.classList.add('bit');

    button.addEventListener('click', () => {
      toggleBit(row, index);
      updateBit(row, index);
    });

    return button;
  }

  function draw() {
    let rowContainer = undefined;
    const stateStr = localStorage.getItem('matrix-state');
    let state;
    if (stateStr) {
      state = JSON.parse(stateStr);
    }
    iterateAll(
      row => {
        rowContainer = document.createElement('div');
        rowContainer.classList.add('row');
        rows[row] = [];
        root.appendChild(rowContainer);
      },
      (row, index) => {
        const button = createBit(row, index);
        rows[row].push({ value: state ? state[row][index] : false, element: button });
        updateBit(row, index);
        rowContainer.appendChild(button);
      }
    );
  }

  function save() {
    const data = [];
    iterateAll(
      row => {
        data[row] = [];
      },
      (row, index) => {
        data[row][index] = rows[row][index].value;
      }
    );
    localStorage.setItem('matrix-state', JSON.stringify(data));
  }

  draw();

  return {
    data: rows,
    set: setBit,
    updateBit,
    update,
    clear,
    save
  };
}
