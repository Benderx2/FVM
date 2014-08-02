macro DEFINE_FUNCTION name, offset {	
	db name, 0
	dd offset
}
