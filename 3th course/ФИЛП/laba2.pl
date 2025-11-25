member(X, [X | _]) :- !.
member(X, [_ | T]) :- member(X, T).

union([], B, B) :- !.
union([X | Xs], B, R) :-
    member(X, B), !,
    union(Xs, B, R).
union([X | Xs], B, [X | R]) :-
    union(Xs, B, R).

intersect([], _, []) :- !.
intersect([X | Xs], B, [X | R]) :-
    member(X, B), !,
    intersect(Xs, B, R).
intersect([_ | Xs], B, R) :-
    intersect(Xs, B, R).

difference([], _, []) :- !.
difference([X | Xs], B, R) :-
    member(X, B), !,
    difference(Xs, B, R).
difference([X | Xs], B, [X | R]) :-
    difference(Xs, B, R).

test :- 
    write('Тест объединения: '),
    union([1,2,3], [2,3,4], R1), write(R1), nl,
    write('Тест пересечения: '),
    intersect([1,2,3], [2,3,4], R2), write(R2), nl,
    write('Тест разности: '),
    difference([1,2,3], [2,3,4], R3), write(R3), nl.