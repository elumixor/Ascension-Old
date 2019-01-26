import {
  Component, HostListener
} from "@angular/core";
import {OverlayComponent} from "../overlay.component";
import {Module, ModulesService} from "../../modules/modules.service";

@Component({
  selector: "app-modules-overlay",
  templateUrl: `./modules-overlay.component.html`,
  styles: []
})
export class ModulesOverlayComponent {
  readonly maxRows = 4;
  readonly columns: number[] = new Array(
    Math.floor(this.modulesService.modulesAsArray.length / this.maxRows) + 1);

  constructor(private overlay: OverlayComponent, public modulesService: ModulesService) {}

  /**
   * Close modules overlay on key release
   * @param {KeyboardEvent} event
   */
  @HostListener("document:keyup", ["$event"])
  hideSearch(event: KeyboardEvent) {
    if (event.code === "KeyM") this.overlay.close.emit();
  }

  /**
   * Select module based on the key pressed.
   * @param {KeyboardEvent} event
   */
  @HostListener("document:keypress", ["$event"])
  selectModule(event: KeyboardEvent) {
    if (this.overlay.displayed) {
      const code = event.code.match(/[0-9]/g);
      if (code) {
        const asNumber = parseInt(code.toString());
        if (asNumber < this.modulesService.modulesAsArray.length)
          this.modulesService.currentModule = this.modulesService.modulesAsArray[asNumber];
      }
    }
  }
}
