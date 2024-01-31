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

# Optionally, you can adjust the frame range
bpy.context.scene.frame_start = 1
bpy.context.scene.frame_end = 100

# Render the animation
bpy.ops.render.render(animation=True, write_still=False)

# Exit Blender
exit()