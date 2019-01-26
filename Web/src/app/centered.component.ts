import {Component} from "@angular/core";

@Component({
  selector: "app-centered",
  template: `
    <div style="position: relative; top: -50%; left: -50%">
        <ng-content></ng-content>
    </div>`,
  host: {"style": "position: absolute; top: 50%; left: 50%"}
})
export class CenteredComponent {}
