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

        const cell1 = row.insertCell(3)
        const cell2 = row.insertCell(4)

        const text1 = document.createTextNode("Hello");
        const text2 = document.createTextNode("World");

        cell1.appendChild(text1);
        cell2.appendChild(text2);

        cellId.appendChild(document.createTextNode(student.id));
        cellFirstName.appendChild(document.createTextNode(student.firstName));
        cellLastName.appendChild(document.createTextNode(student.lastName));
      });
    })
    .catch((error) => console.error("Error fetching students:", error)); // Handle errors
}
