CREATE TABLE students (
    id_student SERIAL PRIMARY KEY,
    id_faculty INTEGER,
    id_user INTEGER NOT NULL,
    id_career INTEGER,
    group_student INTEGER NOT NULL
);

CREATE TABLE profesors (
    id_profesor SERIAL PRIMARY KEY,
    id_deparment INTEGER NOT NULL,
    id_user INTEGER NOT NULL,
    category VARCHAR(50)
);

CREATE TABLE subjects (
    id_subject SERIAL PRIMARY KEY,
    id_profesor INTEGER,
    n_subject TEXT
);

CREATE TABLE faculties (
    id_faculty SERIAL PRIMARY KEY,
    n_faculty TEXT NOT NULL UNIQUE
);

CREATE TABLE careers_age (
    id_career_age SERIAL PRIMARY KEY,
    age INTEGER NOT NULL,
    id_career INTEGER NOT NULL
);

CREATE TABLE careers (
    id_career SERIAL PRIMARY KEY,
    id_faculty INTEGER NOT NULL,
    n_career VARCHAR(50) NOT NULL,
    duration INTEGER NOT NULL
);

CREATE TABLE careers_age_subjects (
    id_careers_age_subjects SERIAL PRIMARY KEY,
    id_subject INTEGER,
    id_career INTEGER
);

CREATE TABLE evaluations (
    id_evaluation SERIAL PRIMARY KEY,
    id_classe INTEGER,
    id_student INTEGER,
    calification INTEGER,
    evaluation_type VARCHAR(10)
);

CREATE TABLE deparments (
    id_deparment SERIAL PRIMARY KEY,
    n_deparment TEXT UNIQUE
);

CREATE TABLE classes (
    id_classe SERIAL PRIMARY KEY,
    id_career_subject INTEGER,
    cantidad_turnos INTEGER,
    date_assis TIMESTAMP
);

CREATE TABLE assistances (
    id_assistance SERIAL PRIMARY KEY,
    id_classe INTEGER,
    id_student INTEGER,
    assis BOOLEAN
);

CREATE TABLE users (
    id_user SERIAL PRIMARY KEY,
    CI VARCHAR(11) UNIQUE,
    user_name VARCHAR(15) NOT NULL UNIQUE,
    password_user VARCHAR(60) NOT NULL,
    user_type INTEGER NOT NULL
);

CREATE TABLE personal_dates (
    CI VARCHAR(11) PRIMARY KEY,
    person_n VARCHAR(20) NOT NULL,
    last_name_1 VARCHAR(20) NOT NULL,
    last_name_2 VARCHAR(20) NOT NULL
);

CREATE TABLE students_images (
    id_student_image INTEGER PRIMARY KEY,
    directory_img TEXT NOT NULL UNIQUE,
    id_student INTEGER NOT NULL
);

ALTER TABLE subjects ADD FOREIGN KEY (id_profesor) REFERENCES profesors (id_profesor);
ALTER TABLE profesors ADD FOREIGN KEY (id_deparment) REFERENCES deparments (id_deparment);
ALTER TABLE assistances ADD FOREIGN KEY (id_classe) REFERENCES classes (id_classe);
ALTER TABLE assistances ADD FOREIGN KEY (id_student) REFERENCES students (id_student);
ALTER TABLE evaluations ADD FOREIGN KEY (id_classe) REFERENCES classes (id_classe);
ALTER TABLE evaluations ADD FOREIGN KEY (id_student) REFERENCES students (id_student);
ALTER TABLE profesors ADD FOREIGN KEY (id_user) REFERENCES users (id_user);
ALTER TABLE students ADD FOREIGN KEY (id_user) REFERENCES users (id_user);
ALTER TABLE personal_dates ADD FOREIGN KEY (CI) REFERENCES users (CI);
ALTER TABLE careers_age ADD FOREIGN KEY (id_faculty) REFERENCES faculties (id_faculty);
ALTER TABLE students ADD FOREIGN KEY (id_career) REFERENCES careers_age (id_career_age);
ALTER TABLE careers_age_subjects ADD FOREIGN KEY (id_career) REFERENCES careers_age (id_career_age);
ALTER TABLE careers_age_subjects ADD FOREIGN KEY (id_subject) REFERENCES subjects (id_subject);
ALTER TABLE classes ADD FOREIGN KEY (id_career_subject) REFERENCES careers_age_subjects (id_careers_age_subjects);
ALTER TABLE careers_age ADD FOREIGN KEY (id_career) REFERENCES careers (id_career);
ALTER TABLE students_images ADD FOREIGN KEY (id_student) REFERENCES students (id_student);