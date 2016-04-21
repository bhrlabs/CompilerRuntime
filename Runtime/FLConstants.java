
/**
 * SER 502 Project 2 Group 31.
 * 
 * Flash Programming Language
 * 
 * Flash Keywords for Operations
 */
public enum FLConstants {
	PUSH, HALT, ARGS, DATA, IN_INT, LD_INT, LD_VAR, STORE, GOTO, OUT_INT,
	EQUAL, NOT_EQUAL, GREATER, GREATER_THAN_EQUAL, LT, LESSER_THAN_EQUAL,
	JMP_FALSE,CONDITION_TRUE_JUMP_TO,
	ADD, SUB, MULT, DIVIDE, MODULUS,
	QUIT,PRINT,END_FUNCTION,FUNCTION,CALL_FUNCTION, RETURN;
	
	public static boolean contains(String test) {
	    for (FLConstants e : FLConstants.values()) {
	        if (e.name().toLowerCase().equals(test)) {
	            return true;
	        }
	    }
	    return false;
	}
}
