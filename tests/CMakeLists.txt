
add_executable(compare compare.cpp)
INSTALL(TARGETS compare DESTINATION bin)

if(WIN32)
  set(EXE_NAME synth.exe)
  set(COMPARE_EXE_NAME compare.exe)
else()
  set(EXE_NAME synth)
  set(COMPARE_EXE_NAME compare)
endif()

# these tests should pass
foreach(ID RANGE 6)
add_test(NAME test${ID}
  COMMAND ${CMAKE_COMMAND}
  -DCOMPARE_EXE_FILE=${CMAKE_BINARY_DIR}/bin/${COMPARE_EXE_NAME}
  -DEXE_FILE=${CMAKE_BINARY_DIR}/bin/${EXE_NAME}
    -DINPUT_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test${ID}.mid
    -DOUTPUT_FILE=test${ID}
    -DERR_FILE=test${ID}.stderr
    -DOUT_FILE=test${ID}.stdout
    -DTEST_FILE=${CMAKE_SOURCE_DIR}/tests/test${ID}-0.wav
    -P ${CMAKE_CURRENT_SOURCE_DIR}/Test.cmake
    )
endforeach(ID)

