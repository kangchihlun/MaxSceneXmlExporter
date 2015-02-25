global allMaxFiles = #()
theOutputPath = getSavepath caption:"選擇animation檔存放的位置" 

if theOutputPath != undefined  do
(
	theFiles = getFiles (  (getfilenamepath maxfilePath) +"\\*.max")
	for j = 1 to theFiles.count do
	(
		loadMaxFile theFiles[j]
		HH.exportanimation (theOutputPath +"\\" + maxfileName  )
	)
)
