# Python program for implementation
# of Ford Fulkerson algorithm
from collections import defaultdict

# This class represents a directed graph
# using adjacency matrix representation
class Graph:

	def __init__(self, graph):
		self.graph = graph # residual graph
		self. ROW = len(graph)
		# self.COL = len(gr[0])

	'''Returns true if there is a path from source 's' to sink 't' in
	residual graph. Also fills parent[] to store the path '''

	def BFS(self, s, t, parent):

		# Mark all the vertices as not visited
		visited = [False]*(self.ROW)

		# Create a queue for BFS
		queue = []

		# Mark the source node as visited and enqueue it
		queue.append(s)
		visited[s] = True

		# Standard BFS Loop
		while queue:

			# Dequeue a vertex from queue and print it
			u = queue.pop(0)

			# Get all adjacent vertices of the dequeued vertex u
			# If a adjacent has not been visited, then mark it
			# visited and enqueue it
			for ind, val in enumerate(self.graph[u]):
				if visited[ind] == False and val > 0:
					# If we find a connection to the sink node,
					# then there is no point in BFS anymore
					# We just have to set its parent and can return true
					queue.append(ind)
					visited[ind] = True
					parent[ind] = u
					if ind == t:
						return True

		# We didn't reach sink in BFS starting
		# from source, so return false
		return False
			
	
	# Returns the maximum flow from s to t in the given graph
	def FordFulkerson(self, source, sink):

		# This array is filled by BFS and to store path
		parent = [-1]*(self.ROW)

		max_flow = 0 # There is no flow initially

		# Augment the flow while there is path from source to sink
		while self.BFS(source, sink, parent) :

			# Find minimum residual capacity of the edges along the
			# path filled by BFS. Or we can say find the maximum flow
			# through the path found.
			path_flow = float("Inf")
			s = sink
			while(s != source):
				path_flow = min (path_flow, self.graph[parent[s]][s])
				s = parent[s]

			# Add path flow to overall flow
			max_flow += path_flow

			# update residual capacities of the edges and reverse edges
			# along the path
			v = sink
			while(v != source):
				u = parent[v]
				self.graph[u][v] -= path_flow
				self.graph[v][u] += path_flow
				v = parent[v]

		return max_flow

class ReadInput:
    def __init__(self, inputFile):
        self.inputFile = inputFile

    def parse_lht(self):
        with open(self.inputFile) as f:
            lines = f.readlines()

        return [int(lines[0][0]), int(lines[0][2]), int(lines[0][4])]

    def parse_edges(self):
        with open(self.inputFile) as f:
            lines = f.readlines()

        lines = lines[1:]

        edges = []

        for line in lines:
            edges.append([int(line[0]), int(line[2]), int(line[4]), int(line[6])])
        return (edges)


class Highway:
    def __init__(self, f, t, l, c):
        self.fromCity = f
        self.toCity = t
        self.length = l
        self.capacity = c

    def print(self):
        print(self.fromCity, self.toCity, self.length, self.capacity)

    
def highways_to_graph(lht, highways):
    graph = [
        [0,0,0,0], 
        [0,0,0,0], 
        [0,0,0,0], 
        [0,0,0,0]]

    for highway in highways:
        graph[highway.fromCity][highway.toCity] = highway.capacity

    return graph

if __name__ == "__main__":
    r = ReadInput("Input.txt")
    lht = r.parse_lht()
    highways = r.parse_edges()
    list_of_highways = []
    for highway in highways:
        list_of_highways.append(Highway(highway[0], highway[1], highway[2], highway[3]))

    graph = highways_to_graph(lht, list_of_highways)

    g = Graph(graph)

    source = 0; sink = 3

    print ("The maximum possible flow is %d " % g.FordFulkerson(source, sink))