import {Component, HostListener} from '@angular/core';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent {
  search = false;
  modules = false;

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
