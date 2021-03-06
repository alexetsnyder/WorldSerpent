//system.mjs
import { Point } from './drawing.mjs';

const Keys = {
	W_KEY       : 'w',
	A_KEY       : 'a',
	S_KEY       : 's', 
	D_KEY       : 'd',
	ARROW_UP    : 'ArrowUp',
	ARROW_DOWN  : 'ArrowDown',
	ARROW_LEFT  : 'ArrowLeft', 
	ARROW_RIGHT : 'ArrowRight'
}

class List {
	#array = []

	append(element) {
		this.#array.push(element);
	}

	constructor(array = []) {
		this.#array = array;
	}

	indexOf(element) {
		for (var i in this.#array) {
			if (this.#array[i] === element) {
				return i;
			}
		}
		return -1;
	}

	removeElement(element) {
		var index = this.indexOf(element);
		if (index !== -1) {
			this.remove(index);
		}
	}

	remove(index) {
		if (index >= 0 && index < this.#array.length) {
			this.#array = this.#array.slice(0, index).concat(this.#array.slice(index + 1));
		}
	}

	toArray() {
		return this.#array;
	}
}

class Random {
	#seed = 0
	#rng = null

	get seed() {
		return this.#seed;
	}

	set seed(value) {
		if (this.#seed !== value) {
			this.#seed = value;
			this.#rng = new Math.seedrandom(this.seed);
		}
	}

	constructor(seed=null) {
		if (!IsNullOrUndefined(seed)) {
			this.#seed = seed;
		}
		else {
			this.#seed = (new Date()).getTime().toString();
		}
		this.#rng = new Math.seedrandom(this.seed);
	}

	reSeed() {
		this.#rng = new Math.seedrandom(this.seed);
	}

	from(start, end) {
		var rngNumber = this.#rng()
		return Math.floor((rngNumber * (end - start)) + start);
	}

	choice(list) {
		return list[this.from(0, list.length)];
	}
}

function DrawWithOffset(ctx, object, offset) {
	var savedPos = object.leftTop;
	var newPos = new Point(savedPos.x + offset.x, savedPos.y + offset.y);
	object.setPos(newPos);
	object.draw(ctx);
	object.setPos(savedPos);
}

function IsNullOrUndefined(object) {
	return object === undefined || object === null;
}

export { DrawWithOffset, Random, Keys, List }