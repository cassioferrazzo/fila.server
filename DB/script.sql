/*
Created		28/10/2015
Modified		28/10/2015
Project		
Model			
Company		
Author		
Version		
Database		PostgreSQL 8.1 
*/


/* Create Tables */


Create table "tb_fila"
(
	"id_fila" Serial NOT NULL,
	"ativo" Boolean,
	"codigo" Varchar(10),
	"data" DATE NOT NULL,
	"hora" TIME NOT NULL,
 primary key ("id_fila")
) Without Oids;





