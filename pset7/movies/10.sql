SELECT DISTINCT(people.name) FROM directors
JOIN people on directors.person_id = people.id
JOIN ratings on directors.movie_id = ratings.movie_id
WHERE ratings.rating >= 9.0;