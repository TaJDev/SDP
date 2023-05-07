/****************************************************/
/* Test Case Table */
DROP TABLE IF EXISTS 'testcase';
CREATE TABLE 'testcase' (
  'CourseID' text,
  'Grade' text,
  'SemesterTaken' text
);
INSERT INTO 'testcase' VALUES ('BIOL111','B','F2019'),
('BIOL113','B','F2019'),('CSDP100','A','F2019'),
('EDTE100','A','F2019'),('ENGL101','B','F2019'),
('MATH109','C','F2019'),('PSYC100','A','F2019'),
('BIOL112','A','S2020'),('BIOL114','W','S2020'),
('CSDP221','P','S2020'),('EXSC111','P','S2020'),
('MATH110','P','S2020'),('SPAN101','W','S2020'),
('CSDP222','W','F2020'),('ECON201','B','F2020'),
('ENGL001','S','F2020'),('ENGL102','C','F2020'),
('MATH112','C','F2020'),('SPAN101','W','F2020'),
('BIOL114','B','S2021'),('CSDP222','C','S2021'),
('ENGL203','A','S2021'),('FREN101','A','S2021'),
('MATH211','C','S2021'),('CSDP250','B','F2021'),
('CSDP301','B','F2021'),('CSDP398','B','F2021'),
('MATH309','B','F2021'),('MATH323','B','F2021');
/* CourseID, Grade, SemesterTaken (NYear -> Where N= F(Fall), S(Spring), Su(Summer), W(Winter)) */


/****************************************************/
/* Course Offering Table */
DROP TABLE IF EXISTS 'courseoffr';
CREATE TABLE 'courseoffr' (
  'CourseID' text,
  'CourseOffr' text
);
INSERT INTO 'courseoffr' VALUES ('CSDP100','Fall,Spring'),('CSDP210	','Fall,Spring'),
('CSDP221	','Fall,Spring'),('CSDP222','Fall,Spring'),('CSDP250	','Spring'),
('CSDP301	','Fall'),('CSDP305	','Fall'),('CSDP332	','Spring'),('CSDP351	','Spring'),
('CSDP390	','Fall'),('CSDP398	','Fall'),('CSDP399	','Spring'),('CSDP401	','Spring'),
('CSDP402	','Fall'),('CSDP403	','Spring'),('CSDP404	','Spring'),('CSDP405	','Spring'),
('CSDP431	','Fall'),('CSDP450	','Fall'),('CSDP490	','Fall,Spring'),('CSDP241	','Fall'),
('CSDP341	','Spring'),('CSDP240	','Spring');
/* CourseID, CourseOffr (Where the values are semesters seperated by commas)*/

/****************************************************/
/* CSDP Curriculum Table */
DROP TABLE IF EXISTS 'csdpcirrrrr'; /* Old Table Name for Older Version */
DROP TABLE IF EXISTS 'CSDP_Curriculum';
CREATE TABLE 'CSDP_Curriculum' (
  'CourseID' text NOT NULL,
  'CourseName' text,
  'Prereq1' text,
  'Prereq2' text,
  'Prereq3' text,
  'Credits' int DEFAULT NULL
);
INSERT INTO 'CSDP_Curriculum' VALUES ('CSDP221','Introduction to Computer Programming','MATH110','MATH109','',4),
('CSDP222','Advanced Programming','CSDP221','','',4),
('CSDP250','Data Structures','CSDP222','','',3),
('CSDP301',' Computer Organization and Assembly Language Programming','CSDP222','','',3),
('CSDP305','Software Engineering I','CSDP250','','',3),
('CSDP332','Internet Programming','CSDP222','','',3),
('CSDP351','Computer Architecture','CSDP301','','',3),
('CSDP390','Social, Ethical and legal s in Computer Science','','','',3),
('CSDP398',' Computer and Language Topics A','CSDP222','','',3),
('CSDP399','Computer and Language Topics B','CSDP222','','',3),
('CSDP401','Operating Systems','CSDP250','CSDP301','',3),
('CSDP402','Computer Networks','CSDP250','','',3),
('CSDP403','Computer Language Theory','CSDP301','MATH323','',3),
('CSDP404','Database Management Systems','CSDP250','','',3),
('CSDP450','Algorithms and Data Structures','CSDP250','MATH323','',3),
('CSDP490','Senior Design Project','','','',3),
('CSDP341','Numerical Analysis','CSDP222','MATH211','',3),
('CSDP405','Software Engineering II','CSDP305','','',3),
('CSDP431','Warehousing and Data','CSDP222','MATH232','MATH210',3),
('CSDP498','Selected Topics in Computer Science A','','','',3),
('CSDP499','Selected Topics in Computer Science B','','','',3),
('MATH211','Calculus II','MATH112','','',4),
('MATH232','Introduction to Linear Algebra','MATH112','','',3),
('MATH309','Introduction to Probability','MATH211','','',3),
('MATH323','Introduction to Discrete Structures','CSDP222','','',3),
('MATH360','Statistics for Scientists','MATH309','','',3);
/* Course ID, Course Name, Prereq[1:3] (Where prerequisites are indicated by individual courses) */

/****************************************************/
/* General Education Table */
DROP TABLE IF EXISTS 'gened';
CREATE TABLE 'gened' (
  'CourseID' text NOT NULL,
  'CourseName' text NOT NULL,
  'Prereq1' text,
  'Prereq2' text,
  'Prereq3' text,
  'Credits' int DEFAULT NULL
);
INSERT INTO 'gened' VALUES ('ENGL203','Fundamentals of Contemporary Speech','ENGL101','ENGL102','',3),
('FREN101','Fundamentals of French I','','','',3),
('FREN102','Fundamentals of French II','FREN101','','',3),
('SPAN101','Fundamentals of Spanich I','','','',3),
('SPAN102','Fundamentals os Spanich II','SPAN101','','',3),
('CHIN101','Fundamentals of Chinese I','','','',3),
('CHIN102','Fundamentals of Chinese II','CHIN101','','',3),
('ARAB101','Fundamentals of Arabic I','','','',3),
('ARAB102','Fundamentals of Arabic II','ARAB101','','',3),
('JAPN101','Fundamentals of Japanese I','','','',3),
('JAPN102','Fundamentals of Japanese II','JAPN101','','',3),
('ECON201','ECON 201 Principles of Economics (Macro)','MATH102','','',3),
('ECON201H','ECON 202 Principles of Economics (Macro)(Honors)','','','',3),
('ECON202','ECON 202 Principles of Economics (Micro)','MATH102','','',3),
('ECON202H','ECON 202 Principles of Economics (Micro)(Honors)','','','',3),
('GEOG201','The World Geography I','','','',3),
('GEOG202','The World Geography II','GEOG201','','',3),
('HIST101','History of World Civilization I','','','',3),
('HIST111H','History of World Civilization I(Honors)','','','',3),
('HIST102','History of World Civilization II','HIST101','','',3),
('HIST112H','History of World Civilization II(Honors)','','','',3),
('POLI200','Introduction to American Government','','','',3),
('POLI200H','Introduction to American Government(Honors)','','','',3),
('POLI342','Urban Politics','POLI200','','',3),
('SOCI101','Introduction to Sociology','','','',3),
('SOCI111H','Introduction to Sociology(Honors)','','','',3),
('CRJS101','Introduction to Criminal Justice','','','',3),
('HUEC203','Human Development: A Lifespan Perspective','','','',3),
('HUEC220','Perspectives on Aging','','','',3),
('HUEC361','Contemporary Family s','SOCI101','PSYC100','',3),
('PSYC100','Introduction to Psychology','','','',3),
('SOCI201','Social Problems','','SOCI101','',3),
('SOWK200','Introduction to Social Work ','','','',3),
('SOWK200H','Introduction to Social Work(Honors)','','','',3),
('BIOL111','Principles of Biology I','','','',3),
('BIOL113','Principles of Biology I Laboratory','','','',1),
('BIOL112','Principles of Biology II','BIOL111','','',3),
('BIOL114','Principles of Biology II Laboratory','','','',1),
('CHEM111','Principles of Chemistry I','','','',3),
('CHEM113','Principles of Chemistry Laboratory I','MATH109','','',1),
('CHEM112','Principles of Chemistry II','CHEM111','CHEM113','MATH109',3),
('CHEM114','Principles of Chemistry Laboratory II','CHEM112','','',1),
('MATH112','Calculus I','MATH110','','',4),
('ENGL101','Basic Composition I','','','',3),
('ENGL101H','Basic Composition I(Honors)','','','',3),
('ENGL102','Basic Composition II','','','',3),
('ENGL102H','Basic Composition II(Honors)','','','',3),
('ENGL305','Technical Writing','ENGL101','ENGL102','ENG303',3),
('ENGL310','Advanced Composition','ENGL101','ENGL102','',3),
('CSDP100','Computer Science Orientation','','','',3),
('EXSC111','Personal Health and Fitness','','','',3),
('MATH101', 'Intermediate Algebra', '','','',3),
('MATH109', 'College Algebra', '','','',3),
('MATH110','Trigonometry and Analytic Geometry','MATH109','','',3);


/****************************************************/
