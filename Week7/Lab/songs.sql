-- 1-8.sql

-- 1.sql
-- SQL query to list the names of all songs in the database
SELECT name FROM songs;

-- 2.sql
-- SQL query to list the names of all songs in increasing order of tempo
SELECT name FROM songs ORDER BY tempo;

-- 3.sql
-- SQL query to list names of top 5 longest songs in desc order
SELECT name FROM songs ORDER BY duration_ms DESC LIMIT 5;

-- 4.sql
-- SQL query that lists the names of any song that have danceability, energy
-- and valence greater than .75
SELECT name FROM songs WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;

-- 5.sql
-- SQL query that returns the avg energy of all songs
SELECT AVG(energy) FROM songs;

-- 6.sql
-- SQL query that lists the name of all songs by Post Malone
SELECT name FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Post Malone');

-- 7.sql
-- SQL query that returns avg energy of songs by Drake
SELECT AVG(energy) FROM songs WHERE artist_id = (SELECT id FROM artists WHERE name = 'Drake');

-- 8.sql
-- SQL query that lists names of songs that have features
SELECT name FROM songs WHERE name LIKE '%feat%';
