# test 1
ADD_EXECUTABLE( testData testData.cxx ../dataM.cxx )
TARGET_LINK_LIBRARIES( testData ${VTK_LIBRARIES} )
ADD_TEST(NAME testData COMMAND $<TARGET_FILE:testData> )

# test 2
#ADD_EXECUTABLE( testDisplay testDisplay.cxx ../display.cxx )
#TARGET_LINK_LIBRARIES( testDisplay ${VTK_LIBRARIES} )
#ADD_TEST(NAME testDisplay COMMAND $<TARGET_FILE:testDisplay> )

# test 3
#ADD_EXECUTABLE( testProcessing testProcessing.cxx ../processing.cxx )
#TARGET_LINK_LIBRARIES( testProcessing ${VTK_LIBRARIES} )
#ADD_TEST(NAME testProcessing COMMAND $<TARGET_FILE:testProcessing> )
