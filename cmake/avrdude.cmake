function(avrdude ELF_FILE AVRD_DONGLE AVRD_INTERFACE AVRD_TARGET)

set(INPUT_FILE "${ELF_FILE}")
set(OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/${ELF_FILE}.bin")
set(AVRDUDE "avrdude")
set(AVRDUDE_FLAGS -c ${AVRD_DONGLE} -P ${AVRD_INTERFACE} -p ${AVRD_TARGET} -F noreset)

add_custom_command(TARGET "${INPUT_FILE}" COMMAND "${CMAKE_SIZE}" -B "${INPUT_FILE}")

add_custom_target(reset COMMAND "${AVRDUDE}" ${AVRDUDE_FLAGS})
add_custom_target(erase COMMAND "${AVRDUDE}" ${AVRDUDE_FLAGS} -e)
add_custom_target(program COMMAND "${AVRDUDE}" ${AVRDUDE_FLAGS} -u -U flash:w:"${INPUT_FILE}")

endfunction()
