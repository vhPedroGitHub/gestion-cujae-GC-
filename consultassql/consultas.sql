SELECT id_profesor, person_n, last_name_1, category, n_deparment from (
	select * from (
		select * from (
			(select * from profesors prof 
			INNER JOIN users usr ON prof.id_user = usr.id_user)
		) AS prouser INNER JOIN personal_dates per ON per.CI_identity = prouser.CI_identity  
	) AS sub1 INNER JOIN deparments d ON sub1.id_deparment = d.id_deparment
	
) AS profesor;

SELECT id_career_year, n_career, year FROM (
	SELECT * FROM (
		SELECT * FROM (
			SELECT cy.id_career_year, year, id_career_subject, id_career FROM careers_years cy 
			LEFT JOIN careers_subjects cs ON cy.id_career_year=cs.id_career_year		  
		) AS consult
	) AS consult2
	WHERE id_career_subject IS NULL
) AS consult3 INNER JOIN careers crer ON crer.id_career=consult3.id_career;

SELECT id_subject, n_subject, person_n, last_name_1, category, n_deparment FROM subjects s
INNER JOIN (SELECT id_profesor, person_n, last_name_1, category, n_deparment FROM (
            SELECT * FROM (
                SELECT * FROM (
                    (SELECT * FROM profesors prof 
                    INNER JOIN users usr ON prof.id_user = usr.id_user)
                ) AS prouser INNER JOIN personal_dates per ON per.CI_identity = prouser.CI_identity  
            ) AS sub1 INNER JOIN deparments d ON sub1.id_deparment = d.id_deparment
        ) AS profesor) AS prof
ON s.id_profesor=prof.id_profesor;

SELECT * FROM students WHERE id_career_year IS NULL;

SELECT id_career_year, n_career, year FROM careers_years cy
INNER JOIN careers cr ON cy.id_career=cr.id_career;

SELECT pr.id_profesor, id_subject, n_subject FROM profesors pr
INNER JOIN subjects s ON pr.id_profesor=s.id_profesor;

SELECT u.id_user FROM users u 
INNER JOIN profesors pr ON pr.id_user=u.id_user

SELECT DISTINCT ON(date_class) SUM(cantidad_turnos)AS total_turns 
FROM view_student_assis
GROUP BY id_subject, date_class
LIMIT 1
;

SELECT SUM(cantidad_turnos) AS asistencia FROM view_student_assis
WHERE id_student = 1 AND id_subject = 1 AND assis
GROUP BY assis
;