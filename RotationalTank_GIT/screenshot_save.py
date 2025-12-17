# trace generated using paraview version 5.12.0-RC2
#import paraview
#paraview.compatibility.major = 5
#paraview.compatibility.minor = 12

#### import the simple module from the paraview
from paraview.simple import *
#### disable automatic camera reset on 'Show'
paraview.simple._DisableFirstRenderCameraReset()

# find source
m3foam = OpenDataFile("./m3.foam")
if m3foam:
  print("Success")
else:
  print("Failed")
# create a new 'Slice'
slice1 = Slice(registrationName='Slice1', Input=m3foam)

# get active view
renderView1 = GetActiveViewOrCreate('RenderView')

# show data in view
slice1Display = Show(slice1, renderView1, 'GeometryRepresentation')

# trace defaults for the display properties.
slice1Display.Representation = 'Surface'

# hide data in view
Hide(m3foam, renderView1)

# show color bar/color legend
slice1Display.SetScalarBarVisibility(renderView1, True)

# update the view to ensure updated data information
renderView1.Update()

# get color transfer function/color map for 'p'
pLUT = GetColorTransferFunction('p')

# get opacity transfer function/opacity map for 'p'
pPWF = GetOpacityTransferFunction('p')

# get 2D transfer function for 'p'
pTF2D = GetTransferFunction2D('p')

# toggle interactive widget visibility (only when running from the GUI)
HideInteractiveWidgets(proxy=slice1.SliceType)

renderView1.ResetActiveCameraToNegativeX()

# reset view to fit data
renderView1.ResetCamera(False, 0.9)

# set scalar coloring
ColorBy(slice1Display, ('POINTS', 'alpha.water'))

# Hide the scalar bar for this color map if no visible data is colored by it.
HideScalarBarIfNotNeeded(pLUT, renderView1)

# rescale color and/or opacity maps used to include current data range
slice1Display.RescaleTransferFunctionToDataRange(True, False)

# show color bar/color legend
slice1Display.SetScalarBarVisibility(renderView1, True)

# get color transfer function/color map for 'alphawater'
alphawaterLUT = GetColorTransferFunction('alphawater')

# get opacity transfer function/opacity map for 'alphawater'
alphawaterPWF = GetOpacityTransferFunction('alphawater')

# get 2D transfer function for 'alphawater'
alphawaterTF2D = GetTransferFunction2D('alphawater')

# create a new 'Annotate Time Filter'
annotateTimeFilter1 = AnnotateTimeFilter(registrationName='AnnotateTimeFilter1', Input=slice1)

# set active source
SetActiveSource(annotateTimeFilter1)

# show data in view
annotateTimeFilter1Display = Show(annotateTimeFilter1, renderView1, 'TextSourceRepresentation')

# show data in view
annotateTimeFilter1Display = Show(annotateTimeFilter1, renderView1, 'TextSourceRepresentation')

# get layout
layout1 = GetLayout()

# layout/tab size in pixels
layout1.SetSize(1583, 786)
animationScene1 = GetAnimationScene()
print("AnimationScene:", animationScene1)
# current camera placement for renderView1
renderView1.CameraPosition = [2.7276599337740226, 0.0, 0.046483010053634644]
renderView1.CameraFocalPoint = [0.018169984221458435, 0.0, 0.046483010053634644]
renderView1.CameraViewUp = [0.0, 0.0, 1.0]
renderView1.CameraParallelScale = 0.8485337977642671
print("RenderView Type:", type(renderView1))
SaveAnimation(
    'save.png',
    renderView1,
    FrameRate=16,
    ImageResolution=[1583, 786],
    AnimationScene=animationScene1
)

#================================================================
# addendum: following script captures some of the application
# state to faithfully reproduce the visualization during playback
#================================================================

#--------------------------------
# saving layout sizes for layouts

# layout/tab size in pixels
layout1.SetSize(1583, 786)

#-----------------------------------
# saving camera placements for views

# current camera placement for renderView1
renderView1.CameraPosition = [2.7276599337740226, 0.0, 0.046483010053634644]
renderView1.CameraFocalPoint = [0.018169984221458435, 0.0, 0.046483010053634644]
renderView1.CameraViewUp = [0.0, 0.0, 1.0]
renderView1.CameraParallelScale = 0.8485337977642671


##--------------------------------------------
## You may need to add some code at the end of this python script depending on your usage, eg:
#
## Render all views to see them appears
# RenderAllViews()
#
## Interact with the view, usefull when running from pvpython
# Interact()
#
## Save a screenshot of the active view
# SaveScreenshot("path/to/screenshot.png")
#
## Save a screenshot of a layout (multiple splitted view)
# SaveScreenshot("path/to/screenshot.png", GetLayout())
#
## Save all "Extractors" from the pipeline browser
# SaveExtracts()
#
## Save a animation of the current active view
# SaveAnimation()
#
## Please refer to the documentation of paraview.simple
## https://kitware.github.io/paraview-docs/latest/python/paraview.simple.html
##--------------------------------------------