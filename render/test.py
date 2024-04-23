import bpy
import os
import math
import numpy as np
from scipy.spatial.transform import Rotation as R

# Get the current working directory
current_file_path = os.getcwd()

# Set the output file path for the video
output_path = os.path.join(current_file_path, "rendered_video.mp4")

# Set the rendering parameters for the video
bpy.context.scene.render.image_settings.file_format = 'FFMPEG'
bpy.context.scene.render.ffmpeg.format = 'MPEG4'
bpy.context.scene.render.filepath = output_path

# Define the coordinates and rotation matrix for the cuboid
# Replace these with your actual data
coordinates = [(0, 0, 0), (0, 0, 1), (0, 0, 0)]

# Set the cuboid's size
length = 2
width = 1
height = 3

# Set the cuboid's location
location = coordinates[0]

# Calculate the center of the bounding box
center = np.mean(coordinates, axis=0)

# Calculate the distance from the camera to the object based on the bounding box size
distance = max(length, width, height) * 2

# Set the camera's position
camera_location = (center[0], center[1] + distance, center[2])

# Set the camera's look at position (center of the bounding box)
look_at_position = center

# Set the camera's rotation
rotation_euler = (math.radians(-90), 0, 0)
# Define rotation matrices for each frame
# Replace these with your actual rotation matrices
rotation_matrices = [
    np.array([[0, 1, 0],
              [-1, 0, 0],
              [0, 0, 1]]),
    np.array([[1, 0, 0],
              [0, 1, 0],
              [0, 0, 1]]),
    np.array([[0, 0, 1],
              [0, 1, 0],
              [-1, 0, 0]])
]

# Delete existing objects in the scene
bpy.ops.object.select_all(action='DESELECT')
bpy.ops.object.select_by_type(type='MESH')
bpy.ops.object.delete()

# Create a cuboid and add it to the scene
bpy.ops.mesh.primitive_cube_add(size=1, location=location)
cuboid = bpy.context.object
cuboid.scale = (length/2, width/2, height/2)  # Set the size of the cuboid

# Set up keyframes for the cuboid's location and rotation
location_action = bpy.data.actions.new(name="LocationAction")
rotation_action = bpy.data.actions.new(name="RotationAction")
animation_data = cuboid.animation_data_create()
animation_data.action = location_action

rotation_track = cuboid.animation_data.nla_tracks.new()
rotation_track.name = "RotationTrack"
rotation_strip = rotation_track.strips.new(name="RotationStrip", action=rotation_action, start=1)
rotation_strip.frame_start = 1  # Specify the frame start

# Set up F-Curves for X, Y, and Z location channels
for i in range(3):
    location_action.fcurves.new("location", index=i)

# Set up F-Curves for rotation quaternion
cuboid.rotation_mode = 'QUATERNION'
for i in range(4):
    rotation_action.fcurves.new("rotation_quaternion", index=i)

# Insert keyframes for the location and rotation
for i in range(len(coordinates)):
    frame = i * 30  # Adjust this to set the frame rate
    location = coordinates[i]
    rotation_matrix = rotation_matrices[i]
    
    # Update cuboid's location
    cuboid.location = location
    for j in range(3):
        fcurve = location_action.fcurves.find('location', index=j)
        fcurve.keyframe_points.insert(frame, value=cuboid.location[j])
    
    # Convert rotation matrix to quaternion
    rotation = R.from_matrix(rotation_matrix)
    rotation_quaternion = rotation.as_quat()
    
    # Update cuboid's rotation
    cuboid.rotation_quaternion = rotation_quaternion
    for j in range(4):
        fcurve = rotation_action.fcurves.find('rotation_quaternion', index=j)
        fcurve.keyframe_points.insert(frame, value=rotation_quaternion[j])

# Set interpolation to linear for smooth motion
for fcurve in location_action.fcurves:
    for keyframe in fcurve.keyframe_points:
        keyframe.interpolation = 'LINEAR'
        
for fcurve in rotation_action.fcurves:
    for keyframe in fcurve.keyframe_points:
        keyframe.interpolation = 'LINEAR'

# Optionally, you can adjust the frame range
bpy.context.scene.frame_start = 1
bpy.context.scene.frame_end = len(coordinates) * 30

# Render the animation
bpy.ops.render.render(animation=True, write_still=False)

# Exit Blender
exit()