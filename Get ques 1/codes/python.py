import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Read points from the file
points = []
with open("points.txt", "r") as file:
    for line in file:
        # Remove parentheses and split by commas
        point = line.strip()[1:-1].split(", ")
        points.append([float(coord) for coord in point])

# Convert points to a numpy array for easier handling
points = list(zip(*points))  # Unzips the list of points

# Create a 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot the points
ax.scatter(points[0], points[1], points[2], color='red', s=100)

# Connect the points with a line
ax.plot(points[0], points[1], points[2], color='blue')

# Annotate the points
for i, point in enumerate(zip(*points)):
    ax.text(point[0], point[1], point[2], f'P{i+1} {point}', size=10, zorder=1)

# Set labels
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('3D Plot of Points')

# Show the plot
plt.show()

