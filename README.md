# doczilla-test-tasks

# TASK 1

## Overview

Task 1 concatenates file contents based on their dependency tree. The solution uses topological sort to sort the dependency graph and reveal if it's a CAG. To run the program enter the main directory

## Setup

### 1. Clone the Repository

Clone and access the repository:
```bash
git clone https://github.com/amirshelli/doczilla-test-tasks.git
cd ./doczilla-test-tasks
```

### 2. Build and Run with Makefile

Navigate to application's directory and run the application using makefile:
```bash
cd ./Concatenation
make run arg=<folderName>
```
Replace `<folderName>` with the name of the root folder containing the files you wish to concatenate.

# TASK 2

## Overview

Task 2 contains a simple application that allows managing student records. It consists of a Java-based backend server, a PostgreSQL database, and a client written in Vanilla JavaScript served via NGINX.

## Prerequisites

- **Docker & Docker Compose**
  - [Install Docker](https://docs.docker.com/get-docker/)
  - [Install Docker Compose](https://docs.docker.com/compose/install/)

## Setup

### 1. Clone the Repository

Clone and access the repository:
```bash
git clone https://github.com/amirshelli/doczilla-test-tasks.git
cd ./doczilla-test-tasks
```
### 2. Build and Run with Docker Compose

Navigate to application's directory and run the application using docker-compose:
```bash
cd ./StudentCRUD
docker-compose up --build
```
## Usage
1. Open your browser and navigate to http://localhost:80 to access the web page.
2. Use the interface to:
* Add a student from form.
* Delete student by id.
* View all students.

* API documentation: 
    - GET http://localhost:8080/api/students
    - POST http://localhost:8080/api/students
    - DELETE http://localhost:8080/api/students/{id}
* PostgreSQL: Accessible on localhost:5432

# TASK 3

## Overview

Task 3 implements a simple to-do list application that demonstratres the use of js/jQuery. 

## Prerequisites

- **Docker & Docker Compose**
  - [Install Docker](https://docs.docker.com/get-docker/)
  - [Install Docker Compose](https://docs.docker.com/compose/install/)

## Setup

### 1. Clone the Repository

Clone and access the repository:
```bash
git clone https://github.com/amirshelli/doczilla-test-tasks.git
cd ./doczilla-test-tasks
```

### 2. Build and Run with Docker Compose

Navigate to application's directory and run the application using docker-compose:
```bash
cd ./TodoList
docker-compose up --build
```

## Usage
1. Open your browser and navigate to http://localhost:80 to access the to-do list app.
2. Use the interface to:
* Filter tasks by status (completed or incomplete) and date range.
* Sort tasks by date.
* View task details in a modal by clicking on a task item.

# General Notes
* Ensure Docker and Docker Compose are correctly installed and running on your machine before setting up any of the tasks.
* Each task is independent; navigate to the respective directory before running Docker commands.