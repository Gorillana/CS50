-- 1-13.sql for movies problem

-- 1.sql
-- SQL query to list the titles of all movies released in 08
SELECT title FROM movies WHERE year = '2008';

-- 2.sql
-- SQL query to determine birth year of Emma Stone
SELECT birth FROM people WHERE name = 'Emma Stone';

-- 3.sql
-- SQL query to LIST the titles of all movies with a release date on or after 2018, in alphabetical order
SELECT title FROM movies WHERE year >= '2018' ORDER BY title ASC;

-- 4.sql
-- SQL query to determine the movies with an IMDB rating of 10.0
SELECT COUNT(rating) FROM ratings WHERE rating = '10.0';

-- 5.sql
-- SQL query to list titles and release years of all Harry Potter movies in chronological order
SELECT year, title FROM movies WHERE title LIKE "Harry Potter%" ORDER BY year ASC;

-- 6.sql
-- SQL query to determine the average rating of all movies released in '12
SELECT AVG(rating) FROM ratings JOIN movies ON ratings.movie_id = movies.id
WHERE year = '2012';

-- 7.sql
-- SQL query to list all movies released in 2010 and their ratings, in desc order by rating
-- movies with same rating order alphabetically by title, imitated structure from lecture
SELECT title, rating FROM movies
JOIN ratings ON ratings.movie_id = movies.id
WHERE year = "2010"
ORDER BY rating DESC, title ASC;

-- 8.sql
-- SQL query to list the names of all people who starred in Toy Story
SELECT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.title = "Toy Story";

-- 9.sql
-- SQL query to list the names of all people who starred in a movie
-- released in 04, ordered by birth year
SELECT DISTINCT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE year = '2004'
ORDER BY people.birth ASC;

-- 10.sql
-- SQL query to list the names of all people who directed a movie
-- with a 9 rating or higher
SELECT DISTINCT name FROM people
JOIN directors ON directors.person_id = people.id
JOIN movies ON movies.id = directors.movie_id
JOIN ratings ON ratings.movie_id = movies.id
WHERE rating >= '9.0';

-- 11.sql
-- SQL query to list titles of the five highest rated movies (in order)
-- that Chadwick Boseman starred in, starting with the highest rated
SELECT title FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN ratings ON ratings.movie_id = movies.id
JOIN people ON stars.person_id = people.id
WHERE people.name = "Chadwick Boseman"
ORDER BY rating DESC
LIMIT 5;

-- 12.sql
-- SQL query that lists the titles of all movies in which both 
-- Johnny Depp and Helena Bonham Carter starred
SELECT title FROM movies
JOIN people ON people.id = stars.person_id
JOIN stars ON stars.movie_id = movies.id
WHERE name = "Johnny Depp"
AND title IN (SELECT title FROM movies
JOIN people ON people.id = stars.person_id
JOIN stars ON stars.movie_id = movies.id
WHERE name = "Helena Bonham Carter");

-- 13.sql
-- SQL query to list the names of all people who starred in a movie
-- in which Kevin Bacon also starred Kevin Bacon born in 1958
-- K Bacon wouldn't be included
SELECT DISTINCT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE title IN(
SELECT DISTINCT title FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON stars.movie_id = movies.id
WHERE name = 'Kevin Bacon' AND birth = 1958)
AND name != 'Kevin Bacon';
