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
length = 1
width = 1
height = 1

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

# Delete existing objects in the scene
bpy.ops.object.select_all(action='DESELECT')
bpy.ops.object.select_by_type(type='MESH')
bpy.ops.object.delete()

# Create a slope
bpy.ops.mesh.primitive_plane_add(size=10, location=(0, 0, 0))
slope = bpy.context.object

# Rotate the slope
slope.rotation_euler = (math.radians(30), 0, 0)  # Rotate by 30 degrees along X-axis

# Create a cuboid and add it to the scene
bpy.ops.mesh.primitive_cube_add(size=1, location=(0, 0, height/2))  # Adjust z-location to half of height
cuboid = bpy.context.object
cuboid.scale = (length/2, width/2, height/2)  # Set the size of the cuboid
cuboid.rotation_euler = (math.radians(30), 0, 0)  # Rotate by 30 degrees along X-axis

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
for frame in range(1, 101):  # Assuming 100 frames
    # Update cuboid's location
    location = (0, 0, height/2)  # Move the cuboid along Z-axis
    cuboid.location = location
    for i in range(3):
        fcurve = location_action.fcurves.find('location', index=i)
        fcurve.keyframe_points.insert(frame, value=cuboid.location[i])

    # Set cuboid's rotation to align with the slope's orientation
    slope_normal = slope.data.polygons[0].normal
    target_direction = slope_normal
    current_direction = (0, 0, 1)  # Cuboid's initial orientation
    rotation_quaternion = R.from_matrix([
        current_direction,
        np.cross(current_direction, target_direction),
        np.cross(current_direction, np.cross(current_direction, target_direction))
    ]).as_quat()
    # cuboid.rotation_quaternion = rotation_quaternion
    cuboid.rotation_euler = (math.radians(30), 0, 0)  # Rotate by 30 degrees along X-axis
    for i in range(4):
        fcurve = rotation_action.fcurves.find('rotation_quaternion', index=i)
        fcurve.keyframe_points.insert(frame, value=rotation_quaternion[i])

# Set interpolation to linear for smooth motion
for fcurve in location_action.fcurves:
    for keyframe in fcurve.keyframe_points:
        keyframe.interpolation = 'LINEAR'

for fcurve in rotation_action.fcurves:
    for keyframe in fcurve.keyframe_points:
        keyframe.interpolation = 'LINEAR'

# Optionally, you can adjust the frame range
bpy.context.scene.frame_start = 1
bpy.context.scene.frame_end = 100

# Render the animation
bpy.ops.render.render(animation=True, write_still=False)

# Exit Blender
exit()





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

# Delete existing objects in the scene
bpy.ops.object.select_all(action='DESELECT')
bpy.ops.object.select_by_type(type='MESH')
bpy.ops.object.delete()

maxframe = 1

with open('output', 'r', encoding='utf-8') as datafile:
    # Read the entire file content
    content = datafile.readlines()
    ii = 0
    while ii < len(content):
        content[ii] = content[ii][:-2]
        info = content[ii].split(' ')
        info = [float(word) for word in info]
        type_of_mesh = int(info[0])
        if type_of_mesh == 0:
            settings_of_mesh = info[1:4]
        num = int(info[-1])
        data = []
        for _ in range(num):
            ii += 1
            content[ii] = content[ii][:-2]
            lst = [float(w) for w in content[ii].split(' ')]
            data1 = int(lst[0] * 30 + 0.5)
            data2 = (lst[1], lst[2], lst[3])
            data3 = [[lst[4], lst[5], lst[6]], [lst[7], lst[8], lst[9]], [lst[10], lst[11], lst[12]]]
            data.append((data1, data2, data3))
        ii += 1
        
        if type_of_mesh == 0:
            # Create a cuboid and add it to the scene
            bpy.ops.mesh.primitive_cube_add(size=1, location=data[0][1])
            cuboid = bpy.context.object
            length = settings_of_mesh[0]
            width = settings_of_mesh[1]
            height = settings_of_mesh[2]
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
            for i in range(len(data)):
                frame = data[i][0]  # Adjust this to set the frame rate
                maxframe = max(frame, maxframe)
                location = data[i][1]
                rotation_matrix = data[i][2]
                
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
bpy.context.scene.frame_end = maxframe

# Render the animation
bpy.ops.render.render(animation=True, write_still=False)

# Exit Blender
exit()