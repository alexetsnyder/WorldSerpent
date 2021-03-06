//controller.mjs
import { Point, Rect, Text } from './drawing.mjs';

const Tabs = {
	NO_TAB : 'no tab',
	TAB_01 : 'btnTab01',
	TAB_02 : 'btnTab02'
}

const STARTING_TAB = Tabs.TAB_01;

var ID = 0;

class Object {
	#id = ID
	#shape = null
	#tab = STARTING_TAB

	constructor(shape, tab) {
		this.#id = ID;
		ID += 1;
		this.#shape = shape;
		this.#tab = tab;
	}

	isDraw(tab) {
		return tab === this.#tab;
	}

	draw(ctx) {
		this.#shape.draw(ctx);
	}
}

class Controller {
	#objects = [];
	#currentTab = Tabs.NO_TAB

	constructor() {
		var textTab01 = new Object(new Text('Hello World 01!', new Point(200, 150)), Tabs.TAB_01);
		var textTab02 = new Object(new Text('Hello World 02!', new Point(200, 150)), Tabs.TAB_02);
		var rectTab01 = new Object(new Rect(150, 200, 100, 100, '#FF0000'), Tabs.TAB_01);
		var rectTab02 = new Object(new Rect(150, 200, 100, 100, '#0000FF'), Tabs.TAB_02);
		this.#objects = [textTab01, textTab02, rectTab01, rectTab02];
		this.wire_tab_events();
		this.showTab(STARTING_TAB);
	} 

	wire_tab_events() {
		for (var tab of document.getElementsByClassName('tabLinks')) {
			tab.onclick = (tabEventArgs) => this.onTabClicked(tabEventArgs);
		}
	}

	draw(ctx) {
		for (var obj of this.#objects) {
			if (obj.isDraw(this.#currentTab)) {
				obj.draw(ctx);
			}
		}
	}

	update() {

	}

	showTab(btnTab) {
		var btnTabHTML = document.getElementById(btnTab);

		for (var tabLink of document.getElementsByClassName('tabLinks')) {
			tabLink.className = tabLink.className.replace(' active', '');
		}
		btnTabHTML.className += ' active';
		for (var tabContent of document.getElementsByClassName('tabContent')) {
			tabContent.style.display = 'none';
		}

		this.#currentTab = btnTab;
	
		document.getElementById(this.getTabNameFromBtnName(btnTab)).style.display = 'block'; 
	}

	onTabClicked(tabEventArgs) {
		this.showTab(tabEventArgs.srcElement.id);
	}

	getTabNameFromBtnName(btnName) {
		return btnName.slice(3).toLowerCase();
	}
}

export { Controller };