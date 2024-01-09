def provide_island_edge(grid):

    #helper function that checks to see if in grid (when checking neighbors)
    def is_valid(x, y):
        return 0 <= x < len(grid) and 0 <= y < len(grid[0])

    #dfs helper function
    def dfs(x, y):
        #condition
        if grid[x][y] != "1":
            return
        
        #mark as visited
        grid[x][y] = "2"
        
        #look around visited node
        for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            
            #calculate coord in node next to og node
            new_x = x + dx
            new_y = y + dy

            #sees if on edge of grid or next to node is 0, if yes then add to set
            if not is_valid(new_x, new_y) or grid[new_x][new_y] == "0":
                island_edges.add(x * len(grid[0]) + y)
            else:
                dfs(new_x, new_y)

    #beginning of function
    islands = []
    island_edges = set()

    #cycle through grid
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            #if the node is 1, clear set, do dfs, and if anything is added to the set, put it in the array
            if grid[i][j] == "1":
                island_edges.clear()
                dfs(i, j)
                if island_edges:
                    islands.append(island_edges.copy())

    return islands

#Example 1
grid1 = [
    ["1", "1", "1", "1", "0"],
    ["1", "1", "0", "1", "0"],
    ["1", "1", "0", "0", "0"],
    ["0", "0", "0", "0", "0"]
]
result1 = provide_island_edge(grid1)
print(result1) 

#Example 2
grid2 = [
    ["1", "1", "0", "0", "0"],
    ["1", "1", "0", "0", "0"],
    ["0", "0", "1", "0", "0"],
    ["0", "0", "0", "1", "1"]
]
result2 = provide_island_edge(grid2)
print(result2)