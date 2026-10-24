/**
 * Loads the engine: mlatex.wasm, and mlatex.data with the fonts, from beside
 * mlatex.js unless `locateFile` says where they are.
 */
declare function mLatex(options?: mLatex.Options): Promise<mLatex.Engine>;

declare namespace mLatex {
	/** The package's version, as the engine's VERSION file says. In Node only. */
	const version: string;

	interface Options {
		/** The address of mlatex.wasm or mlatex.data, given its name and mlatex.js's folder. */
		locateFile?: (path: string, prefix: string) => string;
	}

	interface Engine {
		Session: new () => Session;
	}

	/** The values, commands and files every document it makes is handed. */
	interface Session {
		/** A value the document reads with `\variable{name}`. */
		set(name: string, value: string): void;
		unset(name: string): void;
		/** A command the document calls, answered with what `handler` returns. */
		define(name: string, arity: number, handler: (...values: string[]) => unknown): void;
		forget(name: string): void;
		/** A file under the name a document uses for it. */
		provide(name: string, content: Uint8Array | string): void;
		withdraw(name: string): void;
		/** Whether the document was set with nothing reported. */
		typeset(document: string): boolean;
		/** Whether a piece of LaTeX alone was set, on a page cropped to it. */
		snippet(text: string): boolean;
		/** The last PDF made, in bytes of its own. */
		pdf(): Uint8Array;
		/** What went wrong, one error per line. */
		error(): string;
		delete(): void;
	}
}

export = mLatex;
