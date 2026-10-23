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
		/**
		 * Hands over a face to draw what no face mLaTeX carries draws -- a
		 * browser lends a page none of the system's -- as the font file's name
		 * and bytes, such as `NotoSerifCJK-Regular.otf` from `fallback/`.
		 * Every document after looks in it. False for a name with a path in it.
		 */
		font(name: string, bytes: Uint8Array): boolean;
		/** Whether the document was set with nothing reported. */
		typeset(document: string): boolean;
		/** Whether a piece of LaTeX alone was set, on a page cropped to it. */
		snippet(text: string): boolean;
		/** The last PDF made, in bytes of its own. */
		pdf(): Uint8Array;
		/** What went wrong, one error per line. */
		error(): string;
		/** The last PDF's pages, to draw on a canvas; a copy, deleted when done with. */
		screen(): Screen;
		delete(): void;
	}

	/** A canvas's 2D context, a page's or an OffscreenCanvas's. */
	type Context = CanvasRenderingContext2D | OffscreenCanvasRenderingContext2D;

	/** A link on a page, its area in points from the page's top left. */
	interface Link {
		left: number;
		top: number;
		right: number;
		bottom: number;
		/** The address it goes to. */
		target?: string;
		/** Or the page it goes to, from 0, and how far down it in points. */
		page?: number;
		down?: number;
	}

	/**
	 * Where a line of the source was drawn: its area in points from the page's
	 * top left, on one line of the page, the line from 1, and the file's name.
	 */
	interface Spot {
		left: number;
		top: number;
		right: number;
		bottom: number;
		line: number;
		file: string;
	}

	/** Pages drawn by the engine itself onto a canvas, at any size, with no PDF reader. */
	interface Screen {
		/** How many pages there are. */
		count(): number;
		/** A page's width in points. */
		width(page: number): number;
		/** A page's height in points. */
		height(page: number): number;
		/** Draws a page, from 0, at so many pixels to the point. */
		draw(context: Context, page: number, scale: number): void;
		links(page: number): Link[];
		/** Where each line of the source was drawn on a page, for an editor to jump by. */
		spots(page: number): Spot[];
		/**
		 * Every character the pages lack because no face drew it, as code
		 * points: what to fetch a face from `fallback/` for, by what
		 * `fallback/fonts.json` says each draws, before setting them again.
		 */
		missing(): number[];
		/** What the document says of itself. */
		about(): { title: string; author: string; subject: string; keywords: string };
		delete(): void;
	}
}

export = mLatex;
