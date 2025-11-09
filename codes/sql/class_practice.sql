-- -View



-- 01

CREATE VIEW earn AS 
SELECT payment_id, payment_date, amount
FROM payment;

SELECT * FROM earn;



-- 02

CREATE VIEW customer_payment AS
SELECT customer_id, SUM(amount) AS total_payment
FROM payment 
GROUP BY customer_id;

SELECT customer_id, total_payment
FROM customer_payment
WHERE total_payment > 100;




-- Transaction


-- Creating the table

CREATE SCHEMA transaction_data;
USE transaction_data;


CREATE TABLE bankaccounts (
	account_id INT PRIMARY KEY,
	account_name VARCHAR(50),
    balance DECIMAL(10,2)
);


INSERT INTO bankaccounts (account_id, account_name, balance) VALUES
("101", "Alice", "1000"),
("102", "Levin", "1500"),
("103", "Elton", "2000"),
("104", "Asfar", "2500");

-- An example transaction
-- Alice transfers 300 to Levin's account

START TRANSACTION;

UPDATE bankaccounts
SET balance = balance - 300
WHERE account_id = "101";


UPDATE bankaccounts
SET balance = balance + 300
WHERE account_id = "102";

ROLLBACK; -- can't rollback after commit
COMMIT;




-- An index in SQL is a data structure allowing the database to locate data quickly instead of scanning the entire table.


CREATE INDEX idx_account_name ON bankaccounts(account_name);

SELECT * FROM bankaccounts WHERE account_name="Levin";