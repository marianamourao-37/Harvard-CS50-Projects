SELECT title, rating
FROM movies
INNER JOIN ratings on movies.id = ratings.movie_id
WHERE year = 2010
ORDER BY rating DESC, title;