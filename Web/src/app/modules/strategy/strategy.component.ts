import {Component, OnInit} from "@angular/core";
import {StrategyModule} from "./strategy.module";

@Component({
  selector: "app-strategy",
  templateUrl: "./strategy.component.html",
  styleUrls: ["./strategy.component.scss"]
})
export class StrategyComponent implements OnInit {
  constructor(public  module: StrategyModule) {}

  ngOnInit() {}
}
