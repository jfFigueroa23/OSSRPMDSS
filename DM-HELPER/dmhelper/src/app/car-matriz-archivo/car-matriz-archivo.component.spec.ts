import { ComponentFixture, TestBed } from '@angular/core/testing';

import { CarMatrizArchivoComponent } from './car-matriz-archivo.component';

describe('CarMatrizArchivoComponent', () => {
  let component: CarMatrizArchivoComponent;
  let fixture: ComponentFixture<CarMatrizArchivoComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ CarMatrizArchivoComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(CarMatrizArchivoComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
