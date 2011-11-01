#ifndef DFT2LNT_H
#define DFT2LNT_H

// Maximum number of nested files using include statements
#define MAX_FILE_NESTING 100

#include <iostream>
#include <vector>
#include <map>

#include "dft_ast.h"
#include "DFTree.h"

namespace DFT {

class DFT2LNT {
public:
	static int validateCommands(const std::vector<DFT::AST::ASTNode*>* ast) {
		int valid = true;
		for(size_t i=0; i<ast->size(); ++i) {
//			valid = ast->at(i)->validate() ? valid : false;
		}
		return valid;
	}
	static DFTree* createDFT(const std::vector<DFT::AST::ASTNode*>* ast) {
		DFTree* dft = new DFTree();
		for(size_t i=0; i<ast->size(); ++i) {
//			ast->at(i)->handleCommand(dft);
		}
		return dft;
	}
};

/**
 * Every file is associated with an instance of this struct
 */
typedef struct FileContext {
	FILE* fileHandle;
	std::string filename;
	Location loc;
	
	FileContext():
		fileHandle(NULL),
		filename("") {
	}
	FileContext(FILE* fileHandle, std::string& filename, Location& loc):
		fileHandle(fileHandle),
		filename(filename),
		loc(loc) {
	}
} FileContext;

/**
 * The compiler context contains settings and data related to the compilation
 * of a file and its dependencies.
 */
class CompilerContext {
private:
	std::ostream& out;
	unsigned int errors;
	unsigned int warnings;
	std::string name;
	bool m_useColoredMessages;
public:
	map<string,string> types;
	FileContext fileContext[MAX_FILE_NESTING]; // max file nesting of MAX_FILE_NESTING allowed
	int fileContexts;

	class MessageType {
	public:
		enum MType {

			MESSAGE=1,
			WARNING,
			ERROR,

			MESSAGE_FIRST=MESSAGE,
			MESSAGE_LAST =MESSAGE,
			WARNING_FIRST=WARNING,
			WARNING_LAST =WARNING,
			ERROR_FIRST  =ERROR,
			ERROR_LAST   =ERROR,

			NUMBEROF
		};
	private:
		MType type;
	public:
		MessageType(MType type): type(type) {}
		static const MessageType Message;
		static const MessageType Warning;
		static const MessageType Error;
		bool isMessage() { return MESSAGE_FIRST <= type && type <= MESSAGE_LAST; }
		bool isWarning() { return WARNING_FIRST <= type && type <= WARNING_LAST; }
		bool isError()   { return ERROR_FIRST   <= type && type <= ERROR_LAST; }
	};

	/**
	 * Creates a new compiler context with a specific name.
	 */
	CompilerContext(std::ostream& out): out(out), errors(0), warnings(0), name("") {
	}

	~CompilerContext() {
	}

	/**
	 * Push the specified FileContext on the stack.
	 * @param The FileContext to be pushed on the stack.
	 * @return false: success, true: error
	 */
	bool pushFileContext(FileContext context) {
		if(fileContexts>=MAX_FILE_NESTING) {
			reportError("Max file nesting (100) surpassed");
			return true;
		} else {
			fileContext[fileContexts] = context;
			++fileContexts;
		}
		return false;
	}
	
	/**
	 * Pop the top FileContext from the stack.
	 * @return false: success, true: error
	 */
	bool popFileContext() {
		--fileContexts;
		return false;
	}
	
	/**
	 * Returns the current number of file contexts.
	 * @return The current number of file contexts.
	 */
	int getFileContexts() const {
		return fileContexts;
	}
	
	/**
	 * Returns a reference to the FileContext at the specified location
	 * on the stack.
	 * @param i The position in the stack of the FileContext that will be
	 *          returned.
	 * @return The FileContext at the specified location.
	 */
	FileContext& getFileContext(int i) {
		assert(0<=i && i < MAX_FILE_NESTING && "getFileContext(i): invalid i");
		return fileContext[i];
	}
	
	/**
	 * Report the specified error string at the specified location.
	 * The output format is: <file>:<<line>:error:<error>
	 * @param loc The location (file, line number, etc) where the error
	 *            originated from.
	 * @param str The error string to report.
	 */
	void reportErrorAt(Location loc, std::string str);

	/**
	 * Report the specified warning string at the specified location.
	 * The output format is: <file>:<line>:warning:<error>
	 * @param loc The location (file, line number, etc) where the error
	 *            originated from.
	 * @param str The error string to report.
	 */
	void reportWarningAt(Location loc, std::string str);

	/**
	 * Report the specified error, without a location.
	 * The output format is: error:<error>
	 * @param loc The location (file, line number, etc) where the error
	 *            originated from.
	 * @param str The error string to report.
	 */
	void reportError(std::string str);

	/**
	 * Report the specified error, without a location.
	 * The output format is: error:<error>
	 * @param loc The location (file, line number, etc) where the error
	 *            originated from.
	 * @param str The error string to report.
	 */
	void reportWarning(std::string str);

	/**
	 * Returns the number of reported errors.
	 * @return The number of reported errors.
	 */
	unsigned int getErrors() {
		return errors;
	}

	/**
	 * Returns the number of reported warnings.
	 * @return The number of reported warnings.
	 */
	unsigned int getWarnings() {
		return warnings;
	}
	
	void message(std::string str);
	
	void message(std::string str, const MessageType& mType);

	bool testWritable(std::string fileName);

	void useColoredMessages(bool useColoredMessages) {
		m_useColoredMessages = useColoredMessages;
	}
	const bool& usingColoredMessaged() const { return m_useColoredMessages; }

};

} //Namespace: DFT

#endif // DFT2LNT_H
