import {Component, HostListener} from '@angular/core';
import {ModulesControllerService, Module} from "./services/modules-controller.service";

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent {
  search = false;
  modules = false;

  get Module() {
    return Module
  }

  get currentModule() {
    return ModulesControllerService.active
  }

  constructor() {
  }

  @HostListener('document:keydown', ['$event'])
  showSearch(event: KeyboardEvent) {
    if (event.ctrlKey) {
      if (event.code === "KeyM") {
        this.modules = true;
      } else if (event.code === "KeyF") {
        this.search = true;
      }
    }
  }
}
