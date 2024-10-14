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
git clone https://github.com/yourusername/StudentCRUD.git
cd StudentCRUD
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
