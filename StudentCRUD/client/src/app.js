document.addEventListener('DOMContentLoaded', fetchStudents);

function fetchStudents() {
  const table = document
    .getElementById("studentsTable")
    .getElementsByTagName("tbody")[0];
  table.innerHTML = "";

  document
    .getElementById("refreshButton")
    .addEventListener("click", fetchStudents);

  fetch("http://localhost:8080/api/students")
    .then((response) => response.json())
    .then((data) => {
      data.forEach((student) => {
        const row = table.insertRow();
        const cellId = row.insertCell(0);
        const cellFirstName = row.insertCell(1);
        const cellLastName = row.insertCell(2);
        const cellMiddleName = row.insertCell(3);
        const cellBirthDate = row.insertCell(4);
        const cellGroup = row.insertCell(5);

        cellId.appendChild(document.createTextNode(student.id));
        cellFirstName.appendChild(document.createTextNode(student.firstName));
        cellLastName.appendChild(document.createTextNode(student.lastName));
        cellMiddleName.appendChild(document.createTextNode(student.middleName));
        cellBirthDate.appendChild(document.createTextNode(student.birthDate));
        cellGroup.appendChild(document.createTextNode(student.studentGroup));
      });
    })
    .catch((error) => console.error("Error fetching students:", error)); // Handle errors
}
