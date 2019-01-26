import {Component, HostListener, ElementRef, ViewChild, AfterViewInit} from "@angular/core";
import {OverlayComponent} from "../overlay.component";

@Component({
  selector: "app-search-overlay",
  template: `<input type="text" placeholder="Search" class="fz1" #input>`,
  styleUrls: []
})
export class SearchOverlayComponent {
  @ViewChild("input") input: ElementRef;

  constructor(private overlay: OverlayComponent) {
    overlay.inView.subscribe(() => {
      this.input.nativeElement.focus();
    });
  }

  @HostListener("document:keydown", ["$event"])
  hideSearch(event: KeyboardEvent) {
    if (event.code === "Escape") this.overlay.close.emit();
  }

  /* todo

  (After search mechanics is implemented and some results are displayed)

  Center search input with right text alignment

  When search is long enough, or browsing many results,
  lessen search with animation to top left

   */
}
