let dateRange = { start: null, end: null };
let filterCallback = null;

export function stripTime(date) {
  return new Date(date.getFullYear(), date.getMonth(), date.getDate());
}

export function initializeDatePicker() {
  $("#date-range-picker").datepicker({
    dateFormat: "yy-mm-dd",
    onSelect: function (dateText) {
      const selectedDate = stripTime(new Date(dateText));

      if (!dateRange.start || dateRange.end) {
        setDateRange(selectedDate);
      } else if (!dateRange.end) {
        if (selectedDate >= dateRange.start) {
          setDateRange(dateRange.start, selectedDate);
        } else {
          setDateRange(selectedDate);
        }
      }
    },
  });
}

export function setFilterCallback(callback) {
  filterCallback = callback;
}

export function setDateRange(start, end = null) {
  dateRange.start = stripTime(start);
  dateRange.end = end ? stripTime(end) : null;
  if (filterCallback) {
    filterCallback();
  }
}

export function getDateRange() {
  return dateRange;
}
