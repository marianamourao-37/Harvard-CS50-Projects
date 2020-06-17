SELECT DISTINCT(people.name) FROM stars
JOIN people on stars.person_id = people.id
WHERE stars.movie_id IN
(SELECT movie_id FROM stars
JOIN people on stars.person_id = people.id
WHERE people.name = "Kevin Bacon"
AND people.birth = 1958)
AND people.name != "Kevin Bacon";