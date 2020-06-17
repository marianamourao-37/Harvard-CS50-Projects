SELECT title FROM movies
JOIN ratings on movies.id = ratings.movie_id
JOIN stars on movies.id = stars.movie_id
JOIN people on stars.person_id = people.id 
WHERE people.name LIKE "Chadwick Boseman"
ORDER BY ratings.rating DESC 
LIMIT 5;