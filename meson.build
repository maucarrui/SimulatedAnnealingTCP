project('Simulated Annealing TSP', 'cpp')

add_global_arguments('-DSOME_TOKEN=value', language: 'cpp')
sqlite3_dep = dependency('sqlite3')

src = ['src/City.cpp',
       'src/DAO.cpp',
       'src/Graph.cpp',
       'src/Heuristic.cpp',
       'src/main.cpp',
       'src/Solution.cpp']

incdir = include_directories('src')

executable('tsp', 
           src, 
	   dependencies : sqlite3_dep,
	   include_directories : incdir)