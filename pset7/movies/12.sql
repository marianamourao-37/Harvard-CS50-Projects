SELECT title FROM movies
WHERE id IN
(SELECT movie_id FROM stars
JOIN people on stars.person_id = people.id
WHERE people.name = "Johnny Depp")
AND id IN (SELECT movie_id FROM stars
JOIN people on stars.person_id = people.id
WHERE people.name = "Helena Bonham Carter");

