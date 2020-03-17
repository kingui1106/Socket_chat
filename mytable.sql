CREATE DATABASE test;
SHOW DATABASES;
USE test;
DROP DATABASE test;

CREATE TABLE IF NOT EXISTS `mytable1`(
   `name` VARCHAR(100) ,
   `sex` VARCHAR(100) NOT NULL,
   `age` INT NOT NULL,
   `birth` TIMESTAMP,
   PRIMARY KEY ( `name` )
)ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO mytable ( name,sex,age,birth)
                       VALUES
                    ( "kang", "m",18,NOW() );
INSERT INTO mytable ( name,sex,age,birth)
                       VALUES
                    ( "dlrb", "W",18,NOW() );
INSERT INTO mytable1 ( name,sex,age,birth)
                       VALUES
                    ( "ZLQ", "W",15,NOW() ),
					( "WSB", "M",16,NOW() ),
					( "SDS", "W",17,NOW() );
					
SELECT *FROM mytable WHERE age=18;


UPDATE mytable SET birth='1996-12-25' WHERE name='ZLQ';

DELETE FROM mytable WHERE name='JANE';


DELETE FROM mytable;   /*删除表中的所有数据:*/

SELECT * from mytable  WHERE birth LIKE '2019%';  /*模糊查找*/

ALTER TABLE mytable RENAME sectable;  /*表改名*/ 

ALTER TABLE mytable  MOdify  sex VARCHAR(50);    /*字段修改类型*/ 

ALTER TABLE mytable CHANGE sex sexx VARCHAR(30);   /*字段改名改类型*/ 

ALTER TABLE we ADD name varchar(50) not null ;

ALTER TABLE mytable DROP mark;

DROP TABLE IF EXISTS mytable;

SELECT *FROM mytable WHERE age IN(16,18)
ORDER BY name;

SELECT *FROM  mytable WHERE age BETWEEN 16 AND 18 ORDER BY name DESC;

SELECT *FROM mytable where sexx IS NOT NULL;

SELECT DISTINCT age FROM mytable;

SELECT name ,count(*) AS TOTAL FROM mytable GROUP BY age;



INSERT INTO dept(d_no,d_name,d_location) values 
(10,'ACCOUNTING','ShangHai'), 
(20,'RESEARCH','BeiJing'), 
(30,'SALES','ShenZhen'), 
(40,'OPERATIONS','FuJian');


INSERT INTO employee(e_no,e_name,e_gender,dept_no,e_job,e_salary,hireDate)
values
(1001,'SMITH','m',20,'CLERK',800,'2005-11-12'),
(1002,'ALIEN','f',30,'SALESMAN',1600,'2003-05-12'),
(1003,'WARD','f',30,'SALESMAN',1250,'2003-05-12'),
(1004,'JONES','m',20,'MANAGER',2975,'1998-05-18'),
(1005,'MARTIN','m',30,'SALESMAN',1250,'2001-06-12'),
(1006,'BLAKE','f',30,'MANAGER',2850,'1997-02-15'),
(1007,'CLARK','m',10,'MANAGER',2450,'2002-09-12'),
(1008,'SCOTT','m',20,'ANALYST',3000,'2003-05-12'),
(1009,'KING','f',10,'PRESIDENT',5000,'1995-01-01'),
(1010,'TURNER','f',30,'SALESMAN',1500,'1997-10-12'),
(1011,'ADAMS','m',20,'CLERK',1100,'1999-10-05'),
(1012,'CLARK','f',30,'CLERK',950,'2008-06-15');

select *from employee where e_salary in (select max(e_salary) from employee GROUP BY dept_no );


 select dept_no,max(e_salary) from employee GROUP BY dept_no;
 
 
 select dept_no ,avg(e_salary) from employee group by dept_no;
 
 
 
 CREATE TABLE IF NOT EXISTS `we`(
   `id` varchar(50)   NOT NULL  ,
   `passwd` varchar(50) NOT NULL,
   `name` varchar(50) NOT NULL,
   PRIMARY KEY ( `id` )
)ENGINE=InnoDB DEFAULT CHARSET=utf8;


INSERT INTO we(id,passwd)
values
('1234567','1234567');

select *from we where id='123456' and passwd='123456';


INSERT INTO we(name)
values
('cxk');

 
 
 :-1: error: Cannot open D:/????/??/nodeChatClient-master/build-nodeChatClient-Desktop_Qt_5_8_0_MSVC2015_64bit-Debug/debug/moc_predefs.h included by moc file F:\qt\nodeChatClient-master\nodeChatClient-master\mainwindow.h: ????????????????
 
 
 ALTER TABLE we ADD ol INT  not null DEFAULT 0 ;
 
 UPDATE we SET ol=1 WHERE id='ZLQ';
 
 select * from we where ol=0 and id!=1;
 
 
  ALTER TABLE we ADD socket varchar(50)  not null DEFAULT NULL ;


