CREATE DATABASE db_locadora; 
 
CREATE TABLE cliente( 
    id_cliente INTEGER , 
    nome CHARACTER(20) , 
    cpf CHARACTER(20) ,     
    celular CHARACTER(20) , 
    CONSTRAINT PK_cliente PRIMARY KEY (id_cliente) 
); 
