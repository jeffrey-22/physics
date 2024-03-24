import bpy
import os

# Get the current working directory
current_file_path = os.getcwd()

# Set the output file path for the video
output_path = os.path.join(current_file_path, "rendered_video.mp4")

# Set the rendering parameters for the video
bpy.context.scene.render.image_settings.file_format = 'FFMPEG'
bpy.context.scene.render.ffmpeg.format = 'MPEG4'
bpy.context.scene.render.filepath = output_path

import math
min_x = -3
max_x = 6
min_y = 0
max_y = 0
min_z = -20
max_z = 0

# Calculate the center of the bounding box
center_x = (max_x + min_x) / 2
center_y = (max_y + min_y) / 2
center_z = (max_z + min_z) / 2

# Calculate the distance from the camera to the object based on the bounding box size
# You can adjust this distance to fit your scene
distance = max(max_x - min_x, max_y - min_y, max_z - min_z) * 2

# Set the camera's position
camera_location = (center_x, center_y + distance, center_z)

# Set the camera's look at position (center of the bounding box)
look_at_position = (center_x, center_y, center_z)

# Set the camera's rotation
# You may want to adjust these angles to fit your scene
rotation_euler = (math.radians(-90), 0, 0)  # Example: rotate camera 90 degrees around the x-axis, 180 degrees around the z-axis


# Set the cube's location keyframes for animation
with open('output', 'r') as f:
    rl = f.readlines()
rl = [x.split(' ')[0] for x in rl]
rl = [(float(x.split(',')[0][1:]), float(x.split(',')[1]), float(x.split(',')[2][:-1])) for x in rl]

bpy.ops.object.select_all(action='DESELECT')
bpy.ops.object.select_by_type(type='MESH')
bpy.ops.object.delete()

# Create a cube and add it to the scene
bpy.ops.mesh.primitive_uv_sphere_add(radius=1, location = (0, 0, 0), scale = (1, 1, 1))

obj = bpy.context.object

translation_action = bpy.data.actions.new(name="TranslationAction")

# Assign the action to the object
obj.animation_data_create()
obj.animation_data.action = translation_action

# Set up F-Curves for X, Y, and Z location channels
for i in range(3):  # 0 for X, 1 for Y, 2 for Z
    translation_action.fcurves.new("location", index=i)

# Insert keyframes for the X location channel
for i in range(1, 100):
    obj.location = rl[i]  # Change this value for different end positions
    for j in range(3):
        fcurve = translation_action.fcurves.find('location', index=j)
        fcurve.keyframe_points.insert(frame=i, value=obj.location[j])

# Set interpolation to linear for smooth motion
for fcurve in translation_action.fcurves:
    for keyframe in fcurve.keyframe_points:
        keyframe.interpolation = 'LINEAR'



bpy.ops.mesh.primitive_uv_sphere_add(radius=1, location = (2, 0, 0), scale = (1, 1, 1))

obj = bpy.context.object

translation_action = bpy.data.actions.new(name="TranslationAction")

# Assign the action to the object
obj.animation_data_create()
obj.animation_data.action = translation_action

# Set up F-Curves for X, Y, and Z location channels
for i in range(3):  # 0 for X, 1 for Y, 2 for Z
    translation_action.fcurves.new("location", index=i)

with open('output', 'r') as f:
    rl = f.readlines()
rl = [x.split(' ')[1] for x in rl]
rl = [(float(x.split(',')[0][1:]), float(x.split(',')[1]), float(x.split(',')[2][:-2])) for x in rl]
# Insert keyframes for the X location channel
for i in range(1, 100):
    obj.location = rl[i]  # Change this value for different end positions
    for j in range(3):
        fcurve = translation_action.fcurves.find('location', index=j)
        fcurve.keyframe_points.insert(frame=i, value=obj.location[j])

# Set interpolation to linear for smooth motion
for fcurve in translation_action.fcurves:
    for keyframe in fcurve.keyframe_points:
        keyframe.interpolation = 'LINEAR'

# Optionally, you can adjust the frame range
bpy.context.scene.frame_start = 1
bpy.context.scene.frame_end = 100

# Render the animation
bpy.ops.render.render(animation=True, write_still=False)



# Exit Blender
exit()