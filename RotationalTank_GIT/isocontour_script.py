# trace generated using paraview version 5.12.0-RC2
#import paraview
#paraview.compatibility.major = 5
#paraview.compatibility.minor = 12
import os
#### import the simple module from the paraview
from paraview.simple import *
#### disable automatic camera reset on 'Show'
paraview.simple._DisableFirstRenderCameraReset()

# find source
m3foam = OpenDataFile(r"\\wsl$\Ubuntu\home\docencia\2_Matrioska_master\4_SlidingMesh\m3.foam")
#m3foam = FindSource('/home/docencia/2_Matrioska_master/4_SlidingMesh/m3.foam')
if m3foam:
  print("Success")
else:
  print("Failed")
# create a new 'Contour'
contour1 = Contour(registrationName='Contour1', Input=m3foam)

# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'alpha.water']
contour1.Isosurfaces = [0.5]

# get active view
renderView1 = GetActiveViewOrCreate('RenderView')

# show data in view
contour1Display = Show(contour1, renderView1, 'GeometryRepresentation')

# trace defaults for the display properties.
contour1Display.Representation = 'Surface'

# hide data in view
Hide(m3foam, renderView1)

# show color bar/color legend
contour1Display.SetScalarBarVisibility(renderView1, True)

# update the view to ensure updated data information
renderView1.Update()

# get color transfer function/color map for 'alphawater'
alphawaterLUT = GetColorTransferFunction('alphawater')

# get opacity transfer function/opacity map for 'alphawater'
alphawaterPWF = GetOpacityTransferFunction('alphawater')

# get 2D transfer function for 'alphawater'
alphawaterTF2D = GetTransferFunction2D('alphawater')
output_file = r"D:\Usuarios\877575\Documents\extractSurface.csv"
if not os.path.exists(os.path.dirname(output_file)):
    print("La carpeta de destino no existe.")
# create a new 'Extract Surface'
output_file = r"D:\Usuarios\877575\Desktop\extractSurface.csv"
if not os.access(os.path.dirname(output_file), os.W_OK):
    print(f"Cannot write to the directory: {os.path.dirname(output_file)}")
extractSurface1 = ExtractSurface(registrationName='ExtractSurface1', Input=contour1)
# save data
SaveData( r" D:\Usuarios\877575\Documents\extractSurface.csv", proxy=extractSurface1, WriteTimeSteps=1,
    PointDataArrays=['Normals', 'U', 'alpha.water', 'p', 'p_rgh'],
    CellDataArrays=['U', 'alpha.water', 'p', 'p_rgh'],
    FieldDataArrays=['CasePath'],
    AddTimeStep=1,
    AddTime=1)




## https://kitware.github.io/paraview-docs/latest/python/paraview.simple.html
##--------------------------------------------
