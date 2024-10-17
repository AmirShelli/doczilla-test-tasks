# doczilla-test-tasks

# TASK 1

## Overview

Task 1 concatenates file contents based on their dependency tree. The solution uses topological sort to sort the dependency graph and reveal if it's a CAG. To run the program enter the main directory

## Setup

## Build and Run with Makefile

```bash
make run arg=<folderName>
```

# TASK 2

## Overview

Task 2 contains a simple application that allows managing student records. It consists of a Java-based backend server, a PostgreSQL database, and a client written in Vanilla JavaScript served via NGINX.

## Prerequisites

- **Docker & Docker Compose**
  - [Install Docker](https://docs.docker.com/get-docker/)
  - [Install Docker Compose](https://docs.docker.com/compose/install/)

## Setup

### 1. Clone the Repository

```bash
git clone https://github.com/amirshelli/doczilla-test-tasks.git
cd doczilla-test-tasks/StudentCRUD
```

### 2. Build and Run with Docker Compose

```bash
docker-compose up --build
```
* Web page is available at: http://localhost
* API: 
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

```bash
git clone https://github.com/amirshelli/doczilla-test-tasks.git
cd doczilla-test-tasks/TodoList
```

### 2. Build and Run with Docker Compose

```bash
docker-compose up --build
```
* Web page is available at: http://localhost

* Client-side: The front-end (HTML, CSS, JavaScript) is served via NGINX.
* Server-side: The Node.js server acts as a CORS proxy for the [https://todo.doczilla.pro](https://todo.doczilla.pro/swagger-ui/index.html?configUrl=/v3/api-docs/swagger-config) site.

