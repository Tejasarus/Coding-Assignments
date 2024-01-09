import heapq

def heuristic_distance(candidate, goal):
    return abs(candidate[0] - goal[0]) + abs(candidate[1] - goal[1])

def get_path_from_A_star(start, goal, obstacles):
    def neighbors(current):
        return [(current[0] + 1, current[1]),
                (current[0] - 1, current[1]),
                (current[0], current[1] + 1),
                (current[0], current[1] - 1)]

    OPEN = [] 
    CLOSED = set()
    past_cost = {start: 0}
    parent = {start: None}

    heapq.heappush(OPEN, (0 + heuristic_distance(start, goal), start))

    while OPEN:
        current_cost, current_node = heapq.heappop(OPEN)

        if current_node in CLOSED:
            continue

        CLOSED.add(current_node)

        if current_node == goal:
            path = []
            while current_node:
                path.append(current_node)
                current_node = parent[current_node]
            return path[:-1][::-1] 

        for neighbor in neighbors(current_node):
            if neighbor in obstacles:
                continue

            tentative_past_cost = past_cost[current_node] + 1
            if neighbor not in past_cost or tentative_past_cost < past_cost[neighbor]:
                past_cost[neighbor] = tentative_past_cost
                parent[neighbor] = current_node
                total_cost = tentative_past_cost + heuristic_distance(neighbor, goal)
                heapq.heappush(OPEN, (total_cost, neighbor))

    return []

#start = (4, -1)
#goal = (-1, 3)
#obstacles = [(-3, 0), (-2, 1), (-1, 2), (0, 3), (1, 4), (1, 5)]
#path = get_path_from_A_star(start, goal, obstacles)
#print(path)
