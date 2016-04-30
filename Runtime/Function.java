import java.util.ArrayList;
import java.util.List;

/**
 * SER 502 Project 2 Group 31.
 * 
 * Flash Programming Language
 * 
 * Class corresponding to function definition.
 * 
 */
public class Function {

	String name;
	int lineNum;
	List<String> params;
	
	public Function(String name, int lineNum, List<String> params){
		this.name  = name;
		this.lineNum = lineNum;
		this.params = params;
	}
}
