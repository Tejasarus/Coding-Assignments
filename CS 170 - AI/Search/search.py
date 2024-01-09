from typing import List, Tuple
import heapq
import math
class SearchAlgorithm:

    # Implement Uniform search
    @staticmethod
    def uniform_search(grid: List[List[str]]) -> Tuple[int, List[List[str]]]:
        # Your code here
        start_row, start_col = None, None
        for i in range(len(grid)):
            for j in range(len(grid[i])):
                if grid[i][j] == 's':
                    start_row = i
                    start_col = j
                    break
        
        priority_queue = []  
        heapq.heappush(priority_queue, (0, start_row, start_col))
        visited = set()
        count = 1

        while priority_queue:
            cost, row, col = heapq.heappop(priority_queue)

            if grid[row][col] == 't':
                return 1, grid
            
            if (row, col) not in visited:
                visited.add((row, col))

                if(grid[row][col] != 's'):
                    grid[row][col] = str(count)
                    count += 1

                directions = [(-1, 0), (0, -1), (1, 0), (0, 1)]
                for dr, dc in directions:
                    new_row, new_col = row + dr, col + dc
                    if 0 <= new_row < len(grid) and 0 <= new_col < len(grid[0]) and grid[new_row][new_col] != '-1':
                        new_cost = cost + 1
                        heapq.heappush(priority_queue, (new_cost, new_row, new_col))
                        
        return -1, grid
        pass

    # Implement Depth First Search
    @staticmethod
    def dfs(grid: List[List[str]]) -> Tuple[int, List[List[str]]]:
        # Your code here
        start_row, start_col = None, None
        for i in range(len(grid)):
            for j in range(len(grid[i])):
                if grid[i][j] == 's':
                    start_row = i
                    start_col = j
                    break

        #print(start_row)
        #print(start_col)
        stack = []
        found = -1
        found = SearchAlgorithm.dfs_helper(grid, start_row, start_col, stack)
        num = 1
        for i in stack[1:]:
            for j in i:
                grid[j[0]][j[1]] = str(num)
                num = num + 1
        if found:
            found = 1
        else:
            found = -1
        return found, grid
            
        pass
    
    @staticmethod
    def dfs_helper(grid, row, col, stack):
        if(grid[row][col]) == 't':
            return True
        stack.append({(row,col)})
        # print("Appended: " + str(row) + " " + str(col))

        directions = [(-1, 0), (0, -1), (1, 0), (0, 1)]
        for dr, dc in directions:
            if 0 <= row + dr < len(grid) and 0 <= col+dc < len(grid[0]) and grid[row+dr][col+dc] != '-1' and {(row+dr, col+dc)} not in stack:
                # print("Checking: " + str(row+dr) + " " + str(col+dc) + " for " + str(row) + " " + str(col) + " which is: " + str(grid[row+dr][col+dc]))
                
                if(SearchAlgorithm.dfs_helper(grid, row+dr, col+dc, stack)):
                    return True
        return False


    # Implement Breadth First Search
    @staticmethod
    def bfs(grid: List[List[str]]) -> Tuple[int, List[List[str]]]:
        # Your code here
        queue = []
        visited = set()
        start_row, start_col = None, None

        for i in range(len(grid)):
            for j in range(len(grid[i])):
                if grid[i][j] == 's':
                    start_row = i
                    start_col = j
                    queue.append((i, j))
                    visited.add((i, j))
                    break

        count = 1
        while queue:
            row, col = queue.pop(0)

            if grid[row][col] == 't':
                return 1,grid

            if grid[row][col] != 's':
                grid[row][col] = str(count)
                count += 1
            print(str(row) + " " + str(col) + " " + str(grid[row][col]))
            
            

            directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
            for dr, dc in directions:
                new_row, new_col = row + dr, col + dc
                if 0 <= new_row < len(grid) and 0 <= new_col < len(grid[0]) and grid[new_row][new_col] != '-1' and (new_row, new_col) not in visited:
                    queue.append((new_row, new_col))
                    visited.add((new_row, new_col))
        
        return -1,grid
        pass
    
    # Implement Best First Search
    @staticmethod
    def best_first_search(grid: List[List[str]]) -> Tuple[int, List[List[str]]]:
        start_row, start_col, end_row, end_col = None, None, None, None
        for i in range(len(grid)):
            for j in range(len(grid[i])):
                if grid[i][j] == 's':
                    start_row = i
                    start_col = j
                if grid[i][j] == 't':
                    end_row = i
                    end_col = j

        priority_queue = []
        heapq.heappush(priority_queue, (0, start_row, start_col))
        visited = set()
        count = 1

        while priority_queue:
            cost, row, col = heapq.heappop(priority_queue)

            if grid[row][col] == 't':
                return 1, grid

            if (row, col) not in visited:
                visited.add((row, col))

                if grid[row][col] != 's':
                    grid[row][col] =  str(count)
                    count += 1

                directions = [(-1, 0), (0, -1), (1, 0), (0, 1)]
                for dr, dc in directions:
                    new_row, new_col = row + dr, col + dc
                    if 0 <= new_row < len(grid) and 0 <= new_col < len(grid[0]) and grid[new_row][new_col] != '-1' and (new_row, new_col) not in visited:
                        heuristic = abs(new_row - end_row) + abs(new_col - end_col)
                        heapq.heappush(priority_queue, (heuristic, new_row, new_col))

        return -1, grid
    
    # Implement A* Search
    @staticmethod
    def a_star_search(grid: List[List[str]]) -> Tuple[int, List[List[str]]]:
        # Your code here
        start_row, start_col, end_row, end_col = None, None, None, None
        for i in range(len(grid)):
            for j in range(len(grid[i])):
                if grid[i][j] == 's':
                    start_row = i
                    start_col = j
                if grid[i][j] == 't':
                    end_row = i
                    end_col = j

        priority_queue = []
        heapq.heappush(priority_queue, (0, start_row, start_col, 0))
        visited = set()
        count = 1

        while priority_queue:
            total_cost, row, col, g_cost = heapq.heappop(priority_queue)

            if grid[row][col] == 't':
                return 1, grid

            if (row, col) not in visited:
                visited.add((row, col))

                if grid[row][col] != 's':
                    grid[row][col] = str(count)
                    count += 1 

                directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]
                for dr, dc in directions:
                    new_row, new_col = row + dr, col + dc
                    if 0 <= new_row < len(grid) and 0 <= new_col < len(grid[0]) and grid[new_row][new_col] != '-1' and (new_row, new_col) not in visited:
                        g_cost_new = g_cost + 1
                        heuristic = abs(new_row - end_row) + abs(new_col - end_col)
                        total_cost_new = g_cost_new + heuristic
                        heapq.heappush(priority_queue, (total_cost_new, new_row, new_col, g_cost_new))

        return -1, grid
        

        pass
    
    # Implement Greedy Search
    @staticmethod
    def greedy_search(grid: List[List[str]]) -> Tuple[int, List[List[str]]]:
        # Your code here
        start_row, start_col, end_row, end_col = None, None, None, None
        for i in range(len(grid)):
            for j in range(len(grid[i])):
                if grid[i][j] == 's':
                    start_row = i
                    start_col = j
                if grid[i][j] == 't':
                    end_row = i
                    end_col = j
        print("start:")
        print(start_row,start_col)
        print("end:")
        print(end_row,end_col)
        priority_queue = []
        min_points = []
        heapq.heappush(priority_queue, (0, start_row, start_col))
        visited = set()
        count = 1
        min = 999
        min_r, min_c = start_row, start_col
        
        while priority_queue:
            heuristic, row, col = heapq.heappop(priority_queue)
            print("------------CYCLE-------------")
            if grid[row][col] == 't':
                return 1, grid

            if (row, col) not in visited:
                visited.add((row, col))

                if grid[row][col] != 's':
                    grid[row][col] = str(count)
                    count += 1

                directions = [(0,1),(1,0),(0,-1),(-1,0)]
                for dr, dc in directions:
                    new_row, new_col = row + dr, col + dc
                    if 0 <= new_row < len(grid) and 0 <= new_col < len(grid[0]) and (new_row, new_col) not in visited:
                        #heuristic = math.sqrt((new_row-end_row)**2 + (new_col-end_col)**2)
                        heuristic = abs(new_col - end_col) + abs(new_row - end_row)
                        #print(str(abs(new_col - end_row)) + " + " + str(abs(new_row - end_col)))
                        #h_check = math.sqrt((min_r-end_row)**2 + (min_c-end_col)**2)
                        h_check = abs(min_r - end_row) + abs(min_c - end_col)
                        print("point")
                        print(new_row, new_col ,heuristic, h_check)
                        #print(h_check, heuristic)
                        if heuristic < min and grid[new_row][new_col] != '-1' and heuristic < h_check:
                            print("min")
                            min = heuristic
                            min_r, min_c = new_row, new_col
                            #print(heuristic,min)
      
                heapq.heappush(priority_queue, (heuristic, min_r, min_c))
                            
                #print(min_r, min_c)

        return -1, grid

if __name__ == "__main__":

    example = [
    ['0', '0', '-1', '0', '0', '0', '0', '0', '0', '-1'],
    ['-1', '0', '-1', '0', 't', '-1', '0', '0', '-1', '-1'],
    ['-1', '0', '-1', '0', '0', '0', '0', '-1', '0', '0'],
    ['-1', '0', '0', '0', '0', '0', '0', '-1', '0', '-1'],
    ['-1', '0', '-1', '0', '-1', '-1', '0', '-1', '-1', '-1'],
    ['-1', '0', '0', '0', '-1', '0', '0', '-1', '0', '-1'],
    ['-1', '0', '-1', '-1', '-1', '-1', '0', '0', '0', '-1'],
    ['-1', '0', '0', '-1', 's', '0', '0', '0', '-1', '0'],
    ['0', '-1', '0', '0', '0', '0', '0', '-1', '-1', '0'],
    ['0', '-1', '0', '0', '0', '0', '0', '0', '0', '0']
    ]

    example2 = [
    ['0', '0', '0', '0', '0', '0', '0', '-1', '-1', '0'],
    ['0', '-1', '-1', '-1', '0', '0', '0', '0', '0', '-1'],
    ['-1', '0', '-1', '0', '0', '0', '0', '-1', '0', '0'],
    ['-1', '0', '0', '-1', '0', '-1', '0', '-1', '-1', '-1'],
    ['-1', '0', '0', '0', '0', '0', '-1', '0', '0', '-1'],
    ['0', '0', '0', '-1', '0', '0', '0', '0', '0', '0'],
    ['0', '0', '0', '0', '-1', 's', '0', '-1', '0', '-1'],
    ['0', '-1', '0', '0', 't', '0', '-1', '0', '0', '0'],
    ['-1', '-1', '0', '0', '0', '0', '0', '0', '-1', '0'],
    ['-1', '0', '-1', '0', '-1', '-1', '0', '-1', '0', '-1']
    ]

    example3 = [
    ['0', '0', '-1', '0', '0', '-1', '0', '0', '0', '-1'],
    ['0', '0', '0', '0', '0', '-1', '0', '0', '0', '0'],
    ['0', '0', '0', '0', '0', '0', '0', '-1', '0', '-1'],
    ['0', '0', '-1', '0', '-1', '0', '-1', '0', '-1', '0'],
    ['-1', '0', '0', '0', '0', '0', '0', '-1', '-1', '0'],
    ['0', '0', '0', '0', '-1', '0', '0', '0', '0', '0'],
    ['0', '0', '0', '0', '0', '0', '-1', '0', '0', '0'],
    ['0', '-1', '0', '0', '-1', '0', '0', '0', '0', '-1'],
    ['0', '0', '0', '0', 't', '0', '0', '0', '0', '-1'],
    ['0', '0', '-1', '-1', '0', 's', '0', '0', '-1', '-1']
    ]
    example4 = [
    ['0', '0', '0', '0', '0', '-1', '0', '-1', '0', '-1'],
    ['-1', '0', '-1', '0', '-1', '-1', '0', '-1', '0', '0'],
    ['0', '0', '-1', '0', '0', '0', '0', '0', '-1', '0'],
    ['0', '0', '0', '0', '-1', '-1', '-1', '0', '0', '0'],
    ['0', '0', '-1', '-1', '0', '0', '0', '-1', '0', '0'],
    ['0', '0', '0', '0', '-1', '0', '-1', '-1', '0', '0'],
    ['0', '0', '0', '-1', 's', '-1', '-1', '0', '0', '0'],
    ['-1', '0', '-1', '0', '0', '0', '0', '0', '0', '-1'],
    ['0', '-1', '-1', '0', '0', '0', '0', '-1', '0', '0'],
    ['0', '-1', '0', '0', '-1', '0', '0', '-1', '0', 't']
    ]
    example5 = [
    ['0', '0', '0', '0', '-1', '0', '0', '0', '0', '0'],
    ['0', '0', '0', '-1', '0', '0', '0', '0', '0', '0'],
    ['0', '0', '0', '0', '0', '0', '0', '0', '0', '0'],
    ['0', '-1', '0', '0', '0', '-1', '0', '0', '0', '-1'],
    ['0', '0', '0', '0', '0', '0', '0', '0', '0', '0'],
    ['0', '0', '0', '0', '0', '0', '0', 's', '0', '0'],
    ['0', '0', '0', '0', '0', 't', '0', '0', '0', '0'],
    ['0', '-1', '0', '0', '0', '0', '0', '0', '0', '0'],
    ['0', '0', '0', '0', '0', '0', '0', '0', '0', '0'],
    ['0', '0', '0', '0', '0', '0', '0', '0', '-1', '0']
    ]
    example6 = [
    ['0', '0', '0', '0', '0', '-1', '0', '-1', '0', '-1'],
    ['-1', '0', '-1', '0', '-1', '-1', '0', '-1', '0', '0'],
    ['0', '0', '-1', '0', '0', '0', '0', '0', '-1', '0'],
    ['0', '0', '0', '0', '-1', '-1', '-1', '0', '0', '0'],
    ['0', '0', '-1', '-1', '0', '0', '0', '-1', '0', '0'],
    ['0', '0', '0', '0', '-1', '0', '-1', '-1', '0', '0'],
    ['0', '0', '0', '-1', 's', '-1', '-1', '0', '0', '0'],
    ['-1', '0', '-1', '0', '0', '0', '0', '0', '0', '-1'],
    ['0', '-1', '-1', '0', '0', '0', '0', '-1', '0', '0'],
    ['0', '-1', '0', '0', '-1', '0', '0', '-1', '0', 't']
    ]




    found, final_state = SearchAlgorithm.greedy_search(example6)
    if found == 1:
        print("Target found!")
    else:
        print("Target not found.")

    for row in final_state:
        print(' '.join(row))
