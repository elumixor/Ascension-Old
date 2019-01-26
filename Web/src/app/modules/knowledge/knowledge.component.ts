import { Component, OnInit } from '@angular/core';
import {KnowledgeModule} from "./knowledge.module";

@Component({
  selector: 'app-knowledge',
  templateUrl: './knowledge.component.html',
  styleUrls: ['./knowledge.component.scss']
})
export class KnowledgeComponent implements OnInit {

  constructor(private module: KnowledgeModule) { }

  ngOnInit() {
  }

}
