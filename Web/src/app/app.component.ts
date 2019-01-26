import {Component, HostListener} from "@angular/core";
import {ModulesService} from "./modules/modules.service";

enum Overlays {
  NONE, SEARCH, MODULES
}

@Component({
  selector: "app-root",
  templateUrl: "./app.component.html",
  styleUrls: ["./app.component.scss"]
})
export class AppComponent {
  /**
   * Selected overlay
   * @type {Overlays.NONE}
   */
  private overlay: Overlays = Overlays.NONE;

  /**
   * Represents if the search overlay should be shown
   * @returns {boolean}
   */
  get searchShown(): boolean {
    return this.overlay === Overlays.SEARCH;
  }

  /**
   * Represents if the modules overlay should be shown
   * @returns {boolean}
   */
  get modulesShown(): boolean {
    return this.overlay === Overlays.MODULES;
  }

  constructor(public modulesService: ModulesService) {
  }

  /**
   * React to keys
   * Show overlays on appropriate key combinations
   * @param {KeyboardEvent} event
   */
  @HostListener("document:keydown", ["$event"])
  showSearch(event: KeyboardEvent): void {
    if (event.ctrlKey)
      switch (event.code) {
        case "KeyM":
          this.overlay = Overlays.MODULES;
          break;
        case "KeyF":
          this.overlay = Overlays.SEARCH;
          break;
        default:
          break;
      }
  }

  /**
   * Closes overlays
   */
  closeOverlay(): void {
    this.overlay = Overlays.NONE
  }
}
